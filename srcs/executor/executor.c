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
	t_env_vars	*env_head;
	t_node		*node;

	node = usr_input->head;
	env_head = 
	while(node);
	{
		if (node->token == COMMAND)
			execute_command(node->cmd_split, );
		else if (node->token == OUT || node->token == APPEND)
			redirect_output(node->file_fd);
		else if (node->token == IN)
			redirect_input(node->file_fd);
		else if (node->token == HAREDOC)
			; // Coming Soon
		else if (node->token == PIPE)
			; // Coming Soon
		node = node->next;
	}
	reset
}

/* -------------------------------------------------------------------------- */