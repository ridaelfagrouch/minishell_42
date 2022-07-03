/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	delete_node(t_env_vars *node, t_env_vars **env_head)
{
	t_env_vars	*tracer;

	if (*env_head == node)
		*env_head = (*env_head)->next;
	else
	{
		tracer = *env_head;
		while (tracer->next)
		{
			if (tracer->next == node)
				break ;
			tracer = tracer->next;
		}
		tracer->next = tracer->next->next;
	}
	free(node->key);
	free(node->value);
	free(node);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	unset_cmd(char **input, t_env_vars **env_head)
{
	t_env_vars	*node;
	int			i;
	int			exit_status;

	i = 0;
	exit_status = 0;
	while (input[++i])
	{
		node = get_env_var(input[i], *env_head);
		if (node == NULL)
		{
			exit_status = 1;
			print_err("unset", "not a valid identifier", input[i]);
		}
		else
			delete_node(node, env_head);
	}
	return (exit_status);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */
