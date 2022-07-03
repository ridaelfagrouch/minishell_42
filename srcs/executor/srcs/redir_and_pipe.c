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

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	redirect_input(int new_input_fd)
{
	if (dup2(new_input_fd, STDIN_FILENO) < 0)
		print_err(NULL, "dup2", "input redirection failure");
	close(new_input_fd);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	redirect_output(int new_output_fd)
{
	if (dup2(new_output_fd, STDOUT_FILENO) < 0)
		print_err(NULL, "dup2", "output redirection failure");
	close(new_output_fd);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	output_handler(t_node **node, t_exec *exec)
{
	exec->output = (*node)->file_fd;
}

/* -------------------------------------------------------------------------- *\
TODO-[x]
\* -------------------------------------------------------------------------- */

void	input_handler(t_node **node, t_exec *exec)
{
	if (exec->input != -1)
		close(exec->input);
	exec->input = (*node)->file_fd;
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
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
