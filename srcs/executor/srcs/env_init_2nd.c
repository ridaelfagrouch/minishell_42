/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_2nd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

t_env_vars	*get_last_env_node(t_env_vars *head)
{
	t_env_vars	*node;

	if (head == NULL)
		return (NULL);
	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

/* -------------------------------------------------------------------------- */

void	add_node_to_env(t_env_vars *node, t_env_vars **head)
{
	t_env_vars	*tracer;

	tracer = get_last_env_node(*head);
	if (tracer == NULL)
		tracer = node;
	else
		tracer->next = node;
}

/* -------------------------------------------------------------------------- */

void	free_env(t_env_vars *head)
{
	t_env_vars	*node;
	t_env_vars	*tracer;

	node = head;
	while (node)
	{
		tracer = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = tracer;
	}
}

/* -------------------------------------------------------------------------- */

int	add_key_only(char *input, t_env_vars **head)
{
	t_env_vars	*node;

	node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if (node == NULL)
		return (-1);
	node->key = ft_strdup(input);
	if (node->key == NULL)
		return (free(node), -1);
	add_node_to_env(node, head);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	overwrite_key_value(char *input, t_env_vars **head, char *sep)
{
	char		*key;
	char		*value;
	t_env_vars	*node;

	key = ft_substr(input, 0, (sep - input) / sizeof(char));
	if (key == NULL)
		return (-1);
	node = get_env_var(key, *head);
	value = ft_strdup(sep + 1);
	if (value == NULL)
		return (free(key), -1);	
	free(node->value);
	node->value = value;
	return (0);
}

/* -------------------------------------------------------------------------- */
