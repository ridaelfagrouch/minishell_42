/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 21:37:48 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

int	reset_stds_fd(void)
{
	int	err;

	err = dup2(g_glob_info.d_stdin, STDIN_FILENO);
	if (err < 0)
		return (-1);
	close(g_glob_info.d_stdin);
	g_glob_info.d_stdin = -1;
	err = dup2(g_glob_info.d_stdout, STDOUT_FILENO);
	if (err < 0)
		return (-1);
	close(g_glob_info.d_stdout);
	g_glob_info.d_stdout = -1;
	return (0);
}

/* -------------------------------------------------------------------------- */

int	redirect_input(int new_input_fd)
{
	g_glob_info.d_stdin = dup(STDIN_FILENO);
	if (g_glob_info.d_stdin < 0)
		return (-1);
	if (dup2(new_input_fd, STDIN_FILENO) < 0)
		return (-1);
	close(new_input_fd);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	redirect_output(int new_output_fd)
{
	g_glob_info.d_stdout = dup(STDOUT_FILENO);
	if (g_glob_info.d_stdout < 0)
		return (-1);
	if (dup2(new_output_fd, STDOUT_FILENO) < 0)
		return (-1);
	close(new_output_fd);
	return (0);
}

/* -------------------------------------------------------------------------- */

// int	heredoc_implementation()
// {

// }

/* -------------------------------------------------------------------------- */

int	apply_pipe(int *pipe_stat)
{
	if (*pipe_stat == NO_PIPE)
	{
		if (redirect_input(g_glob_info.d_stdin) != 0)
			return (-1);
		if (pipe(g_glob_info.pipe_fd) != 0)
			return (-1);
		if (redirect_output(g_glob_info.pipe_fd[1]) != 0)
		{
			close(g_glob_info.pipe_fd[0]);
			close(g_glob_info.pipe_fd[1]);
			return (-1);
		}
		*pipe_stat == TO_PIPE;
	}
	else if (*pipe_stat == TO_PIPE)
	{
		if (redirect_output(g_glob_info.d_stdout) != 0)
			return (-1);
		if (redirect_input(g_glob_info.pipe_fd[0]) != 0)
			return (-1);
		*pipe_stat == TO_PIPE;
	}
	return (0);
}

/* -------------------------------------------------------------------------- */