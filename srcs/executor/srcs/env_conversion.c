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

int	init_node(char *env_var, t_env_vars *node)
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
	node->value = ft_strdup(++i + env_var);
	if (node->value == NULL)
		return (free(node->key), -1);
	return (0);
}

/* -------------------------------------------------------------------------- */

char	*get_sorted_env(char **envp)
{
	static int	f_result;
	int			t_result;
	char		*ret_value;
	int			i;
	int			j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[j])
		{
			t_result = ft_strcmp(envp[i], envp[j]);
			if (t_result < f_result)
			{
				f_result = t_result;
				ret_value = env[i];
			}
			j++;
		}
		i++;
	}
}

/* -------------------------------------------------------------------------- */

t_env_vars	*conv_env(char **envp)
{
	t_env_vars	*head;
	t_env_vars	**node;
	char		*srtd_env;
	int			max;
	int			i;

	max = 0;
	while (envp[max])
		max++;
	head = NULL;
	node = &head;
	i = 0;
	while (i++ < max)
	{
		srtd_env = get_sorted_env(envp);
		*node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
		if (*node == NULL || init_node(srtd_env, *node) != 0)
			return (free_env(head), NULL);
		node = &(*node)->next;
	}
	return (head);
}

/* -------------------------------------------------------------------------- */

// char	**split_env_vars_path_var(void)
// {
// 	char	*paths;
// 	char	**splited_paths;

// 	paths = getenv("PATH");
// 	if (paths == NULL)
// 		return (NULL);
// 	splited_paths = ft_split(paths, ':');
// 	return (splited_paths);
// }

/* -------------------------------------------------------------------------- */
