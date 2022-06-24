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

/* -------------------------------------------------------------------------- */

void	delete_node(t_env_vars *node, t_env_vars **env_head)
{
	t_env_vars	**tracer;

	tracer = env_head;
	while ((*tracer) && (*tracer)->next != node)
		(*tracer) = (*tracer)->next;
	(*tracer)->next = (*tracer)->next->next;
	free(node->key);
	free(node->value);
	free(node);
}

/* -------------------------------------------------------------------------- */

int	unset_cmd(char **input, t_env_vars **env_head)
{
	t_env_vars	*node;
	int			i;

	i = 0;
	while (input[++i])
	{
		node = get_env_var(input[i], *env_head);
		if (node == NULL)
			print_err("unset", "not a valid identifier", input[i]);
		else
			delete_node(node, env_head);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
//cttDwlbrO3S@Temp13+