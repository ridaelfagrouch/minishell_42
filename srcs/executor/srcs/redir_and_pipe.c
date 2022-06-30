/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 20:59:48 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

int	reset_stds_fd(void)
{
	int	err;

	err = dup2(g_glob.d_stdin, STDIN_FILENO);
	if (err < 0)
		return (-1);
	close(g_glob.d_stdin);
	g_glob.d_stdin = -1;
	err = dup2(g_glob.d_stdout, STDOUT_FILENO);
	if (err < 0)
		return (-1);
	close(g_glob.d_stdout);
	g_glob.d_stdout = -1;
	return (0);
}

/* -------------------------------------------------------------------------- */

int	redirect_input(int new_input_fd)
{
	if (dup2(new_input_fd, STDIN_FILENO) < 0)
		return (-1);
	close(new_input_fd);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	redirect_output(int new_output_fd)
{
	if (dup2(new_output_fd, STDOUT_FILENO) < 0)
		return (-1);
	close(new_output_fd);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	store_stds(t_execut *execut)
{
	execut->in_fd = -1;
	execut->out_fd = -1;
	g_glob.d_stdin = dup(STDIN_FILENO);
	if (g_glob.d_stdin < 0)
		return (-1);
	g_glob.d_stdout = dup(STDOUT_FILENO);
	if (g_glob.d_stdout < 0)
		return (-1);
	return (0);
}

/* -------------------------------------------------------------------------- */