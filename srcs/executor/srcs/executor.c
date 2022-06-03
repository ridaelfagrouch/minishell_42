/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

static void	free_env_linked_list(t_env *head)
{
	t_env	*node;
	t_env	*tracer;

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

static int	fill_node_with_key_value_env(const char **envp, t_env *node, int node_i)
{
	const char	*env_var;
	int			i;

	env_var	= envp[node_i];
	i = 0;
	while (env_var[i] != '=')
		i++;
	node->key = ft_substr(env_var, 0, i);
	if (node->key == NULL)
		return (-1);
	node->value = ft_strdup(env_var + (++i));
	if (node->value == NULL)
		return (free(node->key), -1);
	return (0);
}

/* -------------------------------------------------------------------------- */

t_env	*convert_env_to_linked_list(const char **envp)
{
	int		nodes_count;
	t_env	*head;
	t_env	**node;
	int		i;

	nodes_count = 0;
	while (envp[nodes_count])
		nodes_count++;
	if (nodes_count == 0)
		return (NULL);
	i = 0;
	head = (t_env *)ft_calloc(1, sizeof(t_env));
	if (head == NULL)
		return (NULL);
	if (fill_node_with_key_value_env(envp, head, i) != 0)
		return (free_env_linked_list(head), NULL);
	node = &head->next;
	while (++i < nodes_count)
	{
		*node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (*node == NULL || fill_node_with_key_value_env(envp, *node, i) != 0)
			return (free_env_linked_list(head), NULL);
		node = &(*node)->next;
	}
	return (head);
}

/* -------------------------------------------------------------------------- */

char	**split_env_path_var(void)
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
