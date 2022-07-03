/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_misc_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	restore_def_values(t_exec *exec, t_node *head)
{
	ignore_signal();
	waitpid(-1, &exec->status, WUNTRACED);
	handle_signals();
	check_invalid_command(head);
	close(exec->output);
	close(exec->input);
	redirect_output(exec->def_std_out);
	redirect_input(exec->def_std_in);
	close_fds(head);
	unlink_heredoc_files(head);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
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
TODO-[X]
\* -------------------------------------------------------------------------- */

int	check_invalid_command(t_node *head)
{
	t_node	*tracer;

	tracer = head;
	while (tracer)
	{
		if (tracer->token == COMMAND && tracer->cmd_flag == -1)
			print_err(NULL, tracer->data, "command not found");
		tracer = tracer->next;
	}
	return (-1);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
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
	if (node->file_fd == -1)
		print_err(NULL, node->data, "no such file or directory!");
	else
		print_err(NULL, node->data, "permission denied");
	while ((*head) && (*head)->token != PIPE)
		(*head) = (*head)->next;
	return (-1);
}
