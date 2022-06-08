/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:46 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/08 13:19:33 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

t_node	*new_node(t_cmds *cmds)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit (1);
	node->token = cmds->token;
	node->data = ft_strdup(cmds->data);
	if (cmds->data)
		free(cmds->data);
	printf ("token:%d | data: %s\n", node->token, node->data);
	return (node);
}

/* -------------------------------------------------------------------------- */

void	add_back(t_node **lst, t_node *node)
{
	t_node	*new;

	if (!node)
		return ;
	if (!lst[0])
	{
		lst[0] = node;
		node->next = node;
		return ;
	}
	new = lst[0];
	while (new->next != lst[0])
		new = new->next;
	node->next = NULL;
}

/* -------------------------------------------------------------------------- */
