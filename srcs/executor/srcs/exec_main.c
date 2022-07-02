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

//// /* -------------------------------------------------------------------------- */
//
//// void	here_doc_(char *delimiter)
//// {
//// 	char	*ptr;
//
//// 	ptr = NULL;
//// 	g_glob.heredoc_fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 00777);
//// 	if (g_glob.heredoc_fd < 0)
//// 	{
//// 		print_err("heredoc", "internal error detected", NULL);
//// 		return ;
//// 	}
//// 	g_glob.heredoc_fd = g_glob.heredoc_fd;
//// 	while (1)
//// 	{
//// 		ptr = readline("> ");
//// 		if (ptr == NULL || ft_strcmp(ptr, delimiter) == 0)
//// 		{
//// 			free(ptr);
//// 			break ;
//// 		}
//// 		ptr = input_expand(put_expand(ptr));
//// 		write(g_glob.heredoc_fd, ptr, ft_strlen(ptr));
//// 		write(g_glob.heredoc_fd, "\n", 1);
//// 		free(ptr);
//// 	}
//// 	close(g_glob.heredoc_fd);
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	redirect_in_out(int *in_fd, int *out_fd)
//// {
//// 	if (*in_fd != -1)
//// 		redirect_input(*in_fd);
//// 	if (*out_fd != -1)
//// 	{
//// 		redirect_output(*out_fd);
//// 		(*out_fd) = -1;
//// 	}
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	redirect_in_out_plus(t_execut *execut, int flag)
//// {
//// 	if (execut->in_fd != -1)
//// 	{
//// 		redirect_input(execut->in_fd);
//// 		execut->in_fd = -1;
//// 	}
//// 	if (execut->out_fd != -1)
//// 		redirect_output(execut->out_fd);
//// 	if (execut->out_fd != -1 && flag == 0)
//// 	{
//// 		execut->pipe_fd[1] = execut->out_fd;
//// 		execut->out_fd = -1;
//// 	}
//// 	if (execut->out_fd == -1 && flag == 0)
//// 		redirect_output(execut->pipe_fd[1]);
//// 	else if (flag == 1)
//// 		dup2(g_glob.d_stdout, STDOUT_FILENO);
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	handel_pipe_exe(t_node *node, t_env_vars **env_head, t_execut *execut)
//// {
//// 	pipe(execut->pipe_fd);
//// 	execut->pid = fork();
//// 	if (execut->pid == 0)
//// 	{
//// 		// ignore_signals();
//// 		redirect_in_out_plus(execut, 0);
//// 		exit(execute_command(node, env_head));
//// 	}
//// 	waitpid(execut->pid, &execut->status, 0);
//// 	close(execut->pipe_fd[1]);
//// 	g_glob.exit = WEXITSTATUS(execut->status);
//// 	execut->in_fd = execut->pipe_fd[0];
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	handel_cmd_exec(t_node *node, t_env_vars **env_head, t_execut *execut)
//// {
//// 	if (execut->in_fd == -1 && ft_strstr_tl(BUILT_INS, node->cmd_split[0]))
//// 	{
//// 		redirect_in_out(&execut->in_fd, &execut->out_fd);
//// 		g_glob.exit = execute_command(node, env_head);
//// 		dup2(g_glob.d_stdout, STDOUT_FILENO);
//// 	}
//// 	else
//// 	{
//// 		execut->pid = fork();
//// 		if (execut->pid == 0)
//// 		{
//// 			redirect_in_out_plus(execut, 1);
//// 			execut->exit_status = execute_command(node, env_head);
//// 			exit(execut->exit_status);
//// 		}
//// 		execut->in_fd = -1;
//// 		waitpid(execut->pid, &execut->status, 0);
//// 		g_glob.exit = WEXITSTATUS(execut->status);
//// 	}
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	handle_heredoc(t_node **node, t_execut *execut)
//// {
//// 	int	status;
//
//// 	g_glob.heredoc_pid = fork();
//// 	if (g_glob.heredoc_pid == 0)
//// 	{
//// 		here_doc_((*node)->data);
//// 		exit(0);
//// 	}
//// 	waitpid(g_glob.heredoc_pid, &status, 0);
//// 	g_glob.exit = WEXITSTATUS(status);
//// 	if (!WIFEXITED(status))
//// 	{
//// 		while ((*node)->next)
//// 			(*node) = (*node)->next;
//// 		g_glob.exit = 1;
//// 	}
//// 	execut->in_fd = open(".tmp", O_RDONLY, 00777);
//// 	g_glob.heredoc_fd = execut->in_fd;
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// void	handel_cmd_herdoc(t_node **node, t_execut *execut, t_env_vars **head)
//// {
//// 	if ((*node)->token == COMMAND)
//// 	{
//// 		if ((*node)->next && (*node)->next->token == PIPE)
//// 			handel_pipe_exe((*node), head, execut);
//// 		else
//// 			handel_cmd_exec((*node), head, execut);
//// 	}
//// 	else if ((*node)->token == HEREDOC)
//// 		handle_heredoc(node, execut);
//// }
//
//// /* -------------------------------------------------------------------------- */
//
//// int	handle_execution(t_info *usr_input, t_env_vars **env_head)
//// {
//// 	t_node		*node;
//// 	t_execut	execut;
//
//// 	store_stds(&execut);
//// 	node = usr_input->head;
//// 	while (node)
//// 	{
//// 		if (node->token == OUT || node->token == APPEND)
//// 			execut.out_fd = node->file_fd;
//// 		else if (node->token == IN)
//// 		{
//// 			if (node->file_fd == -1)
//// 			{
//// 				execut.out_fd = -1;
//// 				while (node && node->token != PIPE)
//// 					node = node->next ;
//// 				continue ;
//// 			}
//// 			execut.in_fd = node->file_fd;
//// 		}
//// 		else if (node->token == COMMAND || node->token == HEREDOC)
//// 			handel_cmd_herdoc(&node, &execut, env_head);
//// 		node = node->next;
//// 	}
//// 	unlink(".tmp");
//// 	return (reset_stds_fd(), 0);
//// }

//* ======================================================================== *//

void	free_double_pointer(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i++] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

// * ====================================================================== * //

void	free_linked_list(t_node *head)
{
	t_node *node;
	t_node *next;

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

// * ====================================================================== * //

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

// * ====================================================================== * //

void	redirect_input(int new_input_fd)
{
	if (dup2(new_input_fd, STDIN_FILENO) < 0)
		print_err(NULL, "dup2", "input redirection failure");
	close(new_input_fd);
}

// * ====================================================================== * //

void	redirect_output(int new_output_fd)
{
	if (dup2(new_output_fd, STDOUT_FILENO) < 0)
		print_err(NULL, "dup2", "output redirection failure");
	close(new_output_fd);
}

// * ====================================================================== * //

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

// * ====================================================================== * //

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

// * ====================================================================== * //

//*	int	restore_def_values(t_exec *exec)
//*	{
//*		if (dup2(exec->def_std_in, STDIN_FILENO) < 0)
//*			return (print_err("dup", "internal error detected", NULL), -1);
//*		if (dup2(exec->def_std_out, STDOUT_FILENO) < 0)
//*			return (print_err("dup", "internal error detected", NULL), -1);
//*		if (close(exec->heredoc) < 0)
//*			return (print_err(NULL, "close", "internal error detected"), -1);
//*		if (unlink(HEREDOC_PATH) < 0)
//*			return (print_err(NULL, "unlink", "internal error detected"), -1);
//*		return (0);
//*	}

// * ====================================================================== * //

void	heredoc_filler(int heredoc, char *delimiter)
{
	char *ptr;

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

// * ====================================================================== * //

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

// * ====================================================================== * //

void	output_handler(t_node **node, t_exec *exec)
{
	exec->output = dup((*node)->file_fd);
	close((*node)->file_fd);
	while ((*node)->next && ((*node)->next->token == APPEND || \
		(*node)->next->token == OUT))
	{
		close((*node)->next->file_fd);
		(*node)->next->file_fd = -1;
		(*node) = (*node)->next;
	}
}

// * ====================================================================== * //
/* -------------------------------------------------------------------------- *\
TODO	Handle errors in IN (input) file_fd
TODO 	If file_fd == -1 then it means it's a Permission Denied error
TODO 	Else if file_fd == -2 then it means it's a File Not Found error
\* -------------------------------------------------------------------------- */

void	input_handler(t_node **node, t_exec *exec)
{
	if ((*node)->file_fd < 0)
		return (print_err("input", "file not found", (*node)->data));
	if (exec->input != -1)
		close(exec->input);
	exec->input = (*node)->file_fd;
}

// * ====================================================================== * //

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

// * ====================================================================== * //

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

// * ====================================================================== * //

t_node	*get_first_heredoc_node(t_node *head)
{
	t_node *tracer;

	tracer = head;
	while (tracer && tracer->token != HEREDOC)
		tracer = tracer->next;
	return (tracer);
}

// * ====================================================================== * //

int	count_heredocs(t_node *head)
{
	t_node *node;
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

// * ====================================================================== * //

char **name_heredoc_files(int count)
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

// * ====================================================================== * //

int	is_invalid_file_fd(t_node *head)
{
	t_node *tracer;
	t_node *node;

	tracer = head;
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
	if (node->file_fd == -1)
		print_err(NULL, "input", "no such file or directory!");
	else
		print_err(NULL, "input", "permission denied");
	//free_linked_list(head);
	return (-1);
}

//* ======================================================================== * //
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

// * ====================================================================== * //
/* -------------------------------------------------------------------------- *\
TODO	Free all allocated memory
free_parsed_data(parsed_data);
\* -------------------------------------------------------------------------- */

int	handle_execution(t_info *parsed_data, t_env_vars **env_head)
{
	t_node	*node;
	t_exec	exec;

	if (set_def_values(&exec) < 0)
		return (-1);
	handle_signals();
	convert_heredoc_to_file(parsed_data->head);
	if (is_invalid_file_fd(parsed_data->head))
		return (-1);
	node = parsed_data->head;
	while (node)
	{
		if (node->token == IN)
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

// * ====================================================================== * //
