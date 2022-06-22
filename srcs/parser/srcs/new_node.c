/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:46 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/22 19:15:16 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	print_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s | ", str[i]);
		i++;
	}
	printf("\n");
}

/* -------------------------------------------------------------------------- */

t_node	*new_node(t_cmds *cmds)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit (1);
	node->token = cmds->token;
	node->data = ft_strdup(cmds->data);
	node->path = ft_strdup(cmds->path);
	node->file_fd = cmds->file_fd;
	if (node->token == COMMAND)
		node->cmd_split = ft_split_cmd(cmds->data);
	else
		node->cmd_split = NULL;
	if (cmds->data)
		free(cmds->data);
	if (cmds->path)
		free(cmds->path);
	// printf ("token:%d | data: %s | path: %s | file_fd = %d\n", \
	// 	node->token, node->data, node->path, node->file_fd);
	// if (node->token == COMMAND)
	// 	print_split(node->cmd_split);
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
