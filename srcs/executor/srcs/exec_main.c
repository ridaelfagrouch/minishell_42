/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/23 17:40:03 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i++] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	free_linked_list(t_node *head)
{
	t_node	*node;
	t_node	*next;

	node = head;
	while (node)
	{
		next = node->next;
		free(node->data);
		close(node->file_fd);
		free(node->path);
		free_double_pointer(node->cmd_split);
		free(node);
		node = next;
	}
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

char	*put_expand(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			ptr[i] = EXPAND;
		i++;
	}
	return (ptr);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	redirect_input(int new_input_fd)
{
	if (dup2(new_input_fd, STDIN_FILENO) < 0)
		print_err(NULL, "dup2", "input redirection failure");
	close(new_input_fd);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	redirect_output(int new_output_fd)
{
	if (dup2(new_output_fd, STDOUT_FILENO) < 0)
		print_err(NULL, "dup2", "output redirection failure");
	close(new_output_fd);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	is_multiple_pipes(t_node *node)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = node;
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	set_def_values(t_exec *exec)
{
	ft_bzero(exec, sizeof(t_exec));
	exec->def_std_in = dup(STDIN_FILENO);
	if (exec->def_std_in < 0)
		return (print_err(NULL, "dup", "internal error detected"), -1);
	exec->def_std_out = dup(STDOUT_FILENO);
	if (exec->def_std_out < 0)
		return (print_err(NULL, "dup", "internal error detected"), -1);
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	exec->input = -1;
	exec->output = -1;
	return (0);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */
/*
*	int	restore_def_values(t_exec *exec)
*		{
*		if (dup2(exec->def_std_in, STDIN_FILENO) < 0)
*			return (print_err("dup", "internal error detected", NULL), -1);
*		if (dup2(exec->def_std_out, STDOUT_FILENO) < 0)
*			return (print_err("dup", "internal error detected", NULL), -1);
*		if (close(exec->heredoc) < 0)
*			return (print_err(NULL, "close", "internal error detected"), -1);
*		if (unlink(HEREDOC_PATH) < 0)
*			return (print_err(NULL, "unlink", "internal error detected"), -1);
*		return (0);
*	}
*/
/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	heredoc_filler(int heredoc, char *delimiter)
{
	char	*ptr;

	while (1)
	{
		ptr = readline("> ");
		if (!ptr || !ft_strcmp(ptr, delimiter))
			break ;
		ptr = input_expand(put_expand(ptr));
		write(heredoc, ptr, ft_strlen(ptr));
		write(heredoc, "\n", 1);
		free(ptr);
		ptr = NULL;
	}
	free(ptr);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	heredoc_handler(char *delimiter, char *filename)
{
	struct sigaction	n_act;
	pid_t				pid;
	int					child_status;
	int					heredoc;

	pid = fork();
	if (pid == 0)
	{
		n_act.sa_handler = SIG_DFL;
		sigaction(SIGINT, &n_act, NULL);
		heredoc = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (heredoc < 0)
		{
			print_err(NULL, "heredoc", "internal error detected");
			exit(1);
		}
		heredoc_filler(heredoc, delimiter);
		exit(0);
	}
	waitpid(pid, &child_status, 0);
	return (WEXITSTATUS(child_status));
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	output_handler(t_node **node, t_exec *exec)
{
	exec->output = (*node)->file_fd;
	while ((*node)->next && ((*node)->next->token == APPEND || \
		(*node)->next->token == OUT))
	{
		close((*node)->next->file_fd);
		(*node)->next->file_fd = -1;
		(*node) = (*node)->next;
	}
}

/* -------------------------------------------------------------------------- *\
TODO	Handle errors in IN (input) file_fd
TODO 	If file_fd == -1 then it means it's a Permission Denied error
TODO 	Else if file_fd == -2 then it means it's a File Not Found error
\* -------------------------------------------------------------------------- */

void	input_handler(t_node **node, t_exec *exec)
{
	if (exec->input != -1)
		close(exec->input);
	exec->input = (*node)->file_fd;
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	pipe_handler(t_node *node, t_exec *exec)
{
	if (node->token == COMMAND)
	{
		if (pipe(exec->pipe) < 0)
			print_err(NULL, "pipe", "internal error detected");
		if (exec->output == -1)
			exec->output = dup(exec->pipe[1]);
		close(exec->pipe[1]);
		exec->pipe[1] = -1;
	}
	else if (node->token == PIPE)
	{
		if (exec->pipe[0] != -1)
		{
			exec->input = dup(exec->pipe[0]);
			close(exec->pipe[0]);
			exec->pipe[0] = -1;
			close(exec->output);
			exec->output = dup(exec->def_std_out);
			redirect_output(exec->output);
			exec->output = -1;
		}
	}
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	command_handler(t_node *head, t_node *node, t_exec *exec, \
	t_env_vars **env_head)
{
	int	exit_status;

	if (node->next && node->next->token == PIPE)
		pipe_handler(node, exec);
	if (exec->output == -1)
		exec->output = dup(exec->def_std_out);
	if (exec->input == -1)
		exec->input = dup(exec->def_std_in);
	redirect_input(exec->input);
	redirect_output(exec->output);
	if (ft_strstr_tl(BUILT_INS, node->cmd_split[0]) && !is_multiple_pipes(head))
		exit_status = execute_builtins(node->cmd_split, env_head);
	else
		exit_status = execute_command(node, env_head);
	exec->input = dup(exec->def_std_in);
	exec->output = dup(exec->def_std_out);
	redirect_input(exec->input);
	redirect_output(exec->output);
	exec->input = -1;
	exec->output = -1;
	return (exit_status);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

t_node	*get_first_heredoc_node(t_node *head)
{
	t_node	*tracer;

	tracer = head;
	while (tracer && tracer->token != HEREDOC)
		tracer = tracer->next;
	return (tracer);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	count_heredocs(t_node *head)
{
	t_node	*node;
	int		count;

	count = 0;
	node = head;
	while (node)
	{
		if (node->token == HEREDOC)
			count++;
		node = node->next;
	}
	return (count);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

char	**name_heredoc_files(int count)
{
	char	**file_names;
	char	*file_name;
	int		i;

	file_names = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!file_names)
		return (NULL);
	i = 0;
	while (i < count)
	{
		file_name = ft_itoa(i);
		file_names[i++] = ft_strjoin(HEREDOC_PATH, file_name);
		free(file_name);
		file_name = NULL;
	}
	return (file_names);
}

/* -------------------------------------------------------------------------- *\
TODO	Print the filenames in the error messages instead of "input"
TODO	Just substitute the commented lines with the ones below
\* -------------------------------------------------------------------------- */

int	is_invalid_file_fd(t_node **head)
{
	t_node	*tracer;
	t_node	*node;

	tracer = *head;
	node = NULL;
	while (tracer)
	{
		if ((tracer->token == IN || tracer->token == OUT || \
			tracer->token == APPEND) && tracer->file_fd < 0)
			node = tracer;
		tracer = tracer->next;
	}
	if (node == NULL)
		return (0);
	/*
	if (node->file_fd == -1)
		print_err(NULL, node->data, "no such file or directory!");
	else
		print_err(NULL, node->data, "permission denied");
	*/
	//? ==================================================================== ?//
	if (node->file_fd == -1)
		print_err(NULL, node->data, "no such file or directory!");
	else
		print_err(NULL, node->data, "permission denied");
	//? ==================================================================== ?//
	while ((*head) && (*head)->token != PIPE)
		(*head) = (*head)->next;
	return (-1);
}

/* -------------------------------------------------------------------------- *\
TODO	Don't free the filenames, only free the array of pointers
\* -------------------------------------------------------------------------- */

int	convert_heredoc_to_file(t_node *head)
{
	t_node	*node;
	char	**file_names;
	int		count;

	count = count_heredocs(head);
	if (count == 0)
		return (0);
	file_names = name_heredoc_files(count);
	if (!file_names || !file_names[0])
		return (free_double_pointer(file_names), -1);
	while (count--)
	{
		node = get_first_heredoc_node(head);
		if (!node)
			return (free_double_pointer(file_names), -1);
		heredoc_handler(node->data, file_names[count]);
		node->file_fd = open(file_names[count], O_RDONLY);
		if (node->file_fd < 0)
			print_err(NULL, "heredoc", "internal error detected");
		free(node->data);
		node->data = file_names[count];
		node->token = IN;
	}
	free(file_names);
	return (0);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	count_command_nodes(t_node *head)
{
	t_node	*tracer;
	int		count;

	count = 0;
	tracer = head;
	while (tracer)
	{
		if (tracer->token == COMMAND)
			count++;
		tracer = tracer->next;
	}
	return (count);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

pid_t	*allocate_child_pid_array(t_exec *exec, t_node *head)
{
	pid_t	*child_pids;
	int		count;
	int		i;

	count = count_command_nodes(head);
	if (count == 0)
		return (NULL);
	child_pids = (pid_t *)ft_calloc(count, sizeof(pid_t));
	if (child_pids == NULL)
		return (NULL);
	i = 0;
	while (i < count)
		child_pids[i++] = -1;
	return (child_pids);
}

/* -------------------------------------------------------------------------- *\
TODO	Free all allocated memory
TODO	The last four lines should be in a function called after the execution
\* -------------------------------------------------------------------------- */

int	handle_execution(t_info *parsed_data, t_env_vars **env_head)
{
	t_node	*node;
	t_exec	exec;

	if (set_def_values(&exec) < 0)
		return (-1);
	handle_signals();
	convert_heredoc_to_file(parsed_data->head);
	exec.childs_pids = allocate_child_pid_array(&exec, parsed_data->head);
	node = parsed_data->head;
	while (node)
	{
		if (node->token == IN && node->token == OUT && \
			node->token == APPEND && is_invalid_file_fd(&node))
			continue ;
		else if (node->token == IN)
			input_handler(&node, &exec);
		else if (node->token == OUT || node->token == APPEND)
			output_handler(&node, &exec);
		else if (node->token == COMMAND)
		{
			if (command_handler(parsed_data->head, node, &exec, env_head) == -1)
				break ;
		}
		else if (node->token == PIPE)
			pipe_handler(node, &exec);
		node = node->next;
	}
	close(exec.output);
	close(exec.input);
	redirect_output(exec.def_std_out);
	redirect_input(exec.def_std_in);
	return (0);
}

/* -------------------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */
