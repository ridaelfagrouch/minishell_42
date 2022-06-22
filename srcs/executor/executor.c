/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

int handle_execution(t_info *usr_input, char **envp)
{
	t_env_vars		*env_head;
	t_node			*node;
	int				exit_status;
	int				pipe_stat;
	int			is_redirected;
	int			to_fork;
	int				pipe_fd[2];

	node = usr_input->head;
	env_head = conv_env(envp);
	pipe_stat = NO_PIPE;
	is_redirected = FALSE;
	to_fork = FALSE;
	while(node);
	{
		if (node->token == COMMAND)
		{
			if (node->next && node->next->token == PIPE && !is_redirected)
			{
				
				to_fork = TRUE;
			}
			exit_status = execute_command(node->cmd_split, env_head, to_fork);
		}
		else if (node->token == OUT || node->token == APPEND)
		{
			is_redirected = TRUE;
			redirect_output(node->file_fd);
		}
		else if (node->token == IN)
			redirect_input(node->file_fd);
		else if (node->token == HAREDOC)
			; // Coming Soon
		node = node->next;
	}
}

/* -------------------------------------------------------------------------- */