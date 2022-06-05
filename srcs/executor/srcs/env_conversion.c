/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

void	free_env_linked_list(t_env_vars *head)
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

int	fill_node_with_key_value_env(char *env_var, t_env_vars *node)
{
	int	i;

	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	i = 0;
	while (env_var[i] && env_var[i] != '=')
		++i;
	node->key = ft_substr(env_var, 0, i);
	if (node->key == NULL)
		return (-1);
	if (env_var[i++] == '=')
	{
		node->value = ft_strdup(env_var + i);
		if (node->value == NULL)
			return (free(node->key), -1);
	}
	else
	{
		node->value = ft_strdup("");
		if (node->value == NULL)
			return (free(node->key), -1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

t_env_vars	*convert_env_vars_to_linked_list(char **envp)
{
	int		nodes_count;
	t_env_vars	*head;
	t_env_vars	**node;
	int		i;

	nodes_count = 0;
	while (envp[nodes_count])
		nodes_count++;
	if (nodes_count == 0)
		return (NULL);
	i = 0;
	head = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if (head == NULL)
		return (NULL);
	if (fill_node_with_key_value_env(envp[i], head) != 0)
		return (free_env_linked_list(head), NULL);
	node = &head->next;
	while (++i < nodes_count)
	{
		*node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
		if (*node == NULL || fill_node_with_key_value_env(envp[i], *node) != 0)
			return (free_env_linked_list(head), NULL);
		node = &(*node)->next;
	}
	return (head);
}

/* -------------------------------------------------------------------------- */

char	**split_env_vars_path_var(void)
{
	char	*paths;
	char	**splited_paths;

	paths = getenv("PATH");
	if (paths == NULL)
		return (NULL);
	splited_paths = ft_split(paths, ':');
	return (splited_paths);
}

/* -------------------------------------------------------------------------- */
