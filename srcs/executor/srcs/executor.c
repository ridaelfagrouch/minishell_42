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

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

void	here_doc_(char *delimiter)
{
	char	*ptr;
	int		file1;

	file1 = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (file1 < 0)
	{
		write(2, "error! opening the tmp\n", 24);
		return ;
	}
	g_glob.heredoc_fd = file1;
	while (1)
	{
		ptr = readline("> ");		// Further testing needed
		if (ptr == NULL)
			break ;
		if (ft_strcmp(ptr, delimiter) == 0)
		{
			free(ptr);
			break ;
		}
		write(file1, ptr, ft_strlen(ptr));
		write(file1, "\n", 1);
		free(ptr);
	}
	close(file1);
	unlink(".tmp");
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
		redirect_input(execut->in_fd);
	if (execut->out_fd != -1)
	{
		redirect_output(execut->out_fd);
		execut->out_fd = -1;
	}
	else if (execut->out_fd == -1 && flag == 0)
		redirect_output(execut->pipe_fd[1]);
	else if (flag == 1)
		dup2(g_glob.d_stdout, STDOUT_FILENO);
}

/* -------------------------------------------------------------------------- */

void	handel_pipe_exe(t_node	*node, t_env_vars **env_head, t_execut *execut)
{
	pipe(execut->pipe_fd);
	execut->pid = fork();
	if (execut->pid == 0)
	{
		redirect_in_out_plus(execut, 0);
		exit(execute_command(node, env_head));
	}
	waitpid(execut->pid, &execut->status, 0);
	close(execut->pipe_fd[1]);
	g_glob.exit = WEXITSTATUS(execut->status);
	execut->in_fd = execut->pipe_fd[0];
}

/* -------------------------------------------------------------------------- */

void	handel_cmd_exec(t_node	*node, t_env_vars **env_head, t_execut *execut)
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

void	handel_cmd_herdoc(t_node **node, t_execut *execut, t_env_vars **env_head)
{
	int	status;

	if ((*node)->token == COMMAND)
	{
		if ((*node)->next && (*node)->next->token == PIPE)
			handel_pipe_exe((*node), env_head, execut);
		else
			handel_cmd_exec((*node), env_head, execut);
	}
	else if ((*node)->token == HAREDOC)
	{
		g_glob.heredoc_pid = fork();
		if (g_glob.heredoc_pid == 0)
		{
			here_doc_((*node)->data);
			exit(0);
		}
		waitpid(g_glob.heredoc_pid, &status, 0);
		if (!WIFEXITED(status))
		{
			while ((*node)->next)
				*node = (*node)->next;
			g_glob.exit = 1;
		}
		execut->in_fd = open(".tmp", O_RDONLY, 00777);
	}
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
		if (node->token == COMMAND || node->token == HAREDOC)
			handel_cmd_herdoc(&node, &execut, env_head);
		node = node->next;
	}
	return (reset_stds_fd(), 0);
}

/* -------------------------------------------------------------------------- */