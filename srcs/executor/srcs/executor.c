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

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

void	here_doc_(char *delimiter)
{
	char	*ptr;

	ptr = NULL;
	g_glob.heredoc_fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (g_glob.heredoc_fd < 0)
	{
		print_err("heredoc", "internal error detected", NULL);
		return ;
	}
	g_glob.heredoc_fd = g_glob.heredoc_fd;
	while (1)
	{
		ptr = readline("> ");
		if (ptr == NULL || ft_strcmp(ptr, delimiter) == 0)
		{
			free(ptr);
			break ;
		}
		ptr = input_expand(put_expand(ptr));
		write(g_glob.heredoc_fd, ptr, ft_strlen(ptr));
		write(g_glob.heredoc_fd, "\n", 1);
		free(ptr);
	}
	close(g_glob.heredoc_fd);
}

/* -------------------------------------------------------------------------- */

void	redirect_in_out(int *in_fd, int *out_fd)
{
	if (*in_fd != -1)
		redirect_input(*in_fd);
	if (*out_fd != -1)
	{
		redirect_output(*out_fd);
		*out_fd = -1;
	}
}

/* -------------------------------------------------------------------------- */

void	redirect_in_out_plus(t_execut *execut, int flag)
{
	if (execut->in_fd != -1)
	{
		redirect_input(execut->in_fd);
		execut->in_fd = -1;
	}
	if (execut->out_fd != -1)
		redirect_output(execut->out_fd);
	if (execut->out_fd != -1 && flag == 0)
	{
		execut->pipe_fd[1] = execut->out_fd;
		execut->out_fd = -1;
	}
	if (execut->out_fd == -1 && flag == 0)
		redirect_output(execut->pipe_fd[1]);
	else if (flag == 1)
		dup2(g_glob.d_stdout, STDOUT_FILENO);
}

/* -------------------------------------------------------------------------- */

void	handel_pipe_exe(t_node *node, t_env_vars **env_head, t_execut *execut)
{
	pipe(execut->pipe_fd);
	execut->pid = fork();
	if (execut->pid == 0)
	{
		// ignore_signals();
		redirect_in_out_plus(execut, 0);
		exit(execute_command(node, env_head));
	}
	waitpid(execut->pid, &execut->status, 0);
	close(execut->pipe_fd[1]);
	g_glob.exit = WEXITSTATUS(execut->status);
	execut->in_fd = execut->pipe_fd[0];
}

/* -------------------------------------------------------------------------- */

void	handel_cmd_exec(t_node *node, t_env_vars **env_head, t_execut *execut)
{
	if (execut->in_fd == -1 && ft_strstr_tl(BUILT_INS, node->cmd_split[0]))
	{
		redirect_in_out(&execut->in_fd, &execut->out_fd);
		g_glob.exit = execute_command(node, env_head);
		dup2(g_glob.d_stdout, STDOUT_FILENO);
	}
	else
	{
		execut->pid = fork();
		if (execut->pid == 0)
		{
			// ignore_signals();
			redirect_in_out_plus(execut, 1);
			execut->exit_status = execute_command(node, env_head);
			exit(execut->exit_status);
		}
		execut->in_fd = -1;
		waitpid(execut->pid, &execut->status, 0);
		g_glob.exit = WEXITSTATUS(execut->status);
	}
}

/* -------------------------------------------------------------------------- */

void	handle_heredoc(t_node **node, t_execut *execut)
{
	int	status;

	g_glob.heredoc_pid = fork();
	if (g_glob.heredoc_pid == 0)
	{
		// ignore_signals();
		here_doc_((*node)->data);
		exit(0);
	}
	waitpid(g_glob.heredoc_pid, &status, 0);
	g_glob.exit = WEXITSTATUS(status);
	if (!WIFEXITED(status))
	{
		while ((*node)->next)
			*node = (*node)->next;
		g_glob.exit = 1;
	}
	execut->in_fd = open(".tmp", O_RDONLY, 00777);
	g_glob.heredoc_fd = execut->in_fd;
}

/* -------------------------------------------------------------------------- */

void	handel_cmd_herdoc(t_node **node, t_execut *execut, t_env_vars **head)
{
	if ((*node)->token == COMMAND)
	{
		if ((*node)->next && (*node)->next->token == PIPE)
			handel_pipe_exe((*node), head, execut);
		else
			handel_cmd_exec((*node), head, execut);
	}
	else if ((*node)->token == HAREDOC)
		handle_heredoc(node, execut);
}

/* -------------------------------------------------------------------------- */

int	handle_execution(t_info *usr_input, t_env_vars **env_head)
{
	t_node		*node;
	t_execut	execut;

	store_stds(&execut);
	node = usr_input->head;
	while (node)
	{
		printf("touken: %d | fd: %d \n", node->token, node->file_fd);
		if (node->token == OUT || node->token == APPEND)
			execut.out_fd = node->file_fd;
		else if (node->token == IN)
		{
			if (node->file_fd == -1)
			{
				execut.out_fd = -1;
				while (node && node->token != PIPE)
					node = node->next ;
				continue ;
			}
			execut.in_fd = node->file_fd;
		}
		else if (node->token == COMMAND || node->token == HAREDOC)
			handel_cmd_herdoc(&node, &execut, env_head);
		node = node->next;
	}
	unlink(".tmp");
	return (reset_stds_fd(), 0);
}

/* -------------------------------------------------------------------------- */
