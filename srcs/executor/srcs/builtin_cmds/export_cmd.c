/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

static char	**copy_envp_keys(t_env_vars *env_vars)
{
	t_env_vars	*node;
	char		**output;
	int			count;
	int			i;

	count = 0;
	node = env_vars;
	while (node->next && ++count)
		node = node->next;
	output = (char **)ft_calloc(count + 1, sizeof(char *));
	if (output == NULL)
		return (NULL);
	i = 0;
	node = env_vars;
	while (i < count && node)
	{
		output[i++] = node->key;
		node = node->next;
	}
	return (output);
}

/* -------------------------------------------------------------------------- */

static char	**get_sorted_env(t_env_vars *env_vars)
{
	char	**cp_env;
	char	*temp;
	int		i;
	int		j;

	cp_env = copy_envp_keys(env_vars);
	if (cp_env == NULL)
		return (NULL);
	i = 0;
	while (cp_env[i])
	{
		j = i + 1;
		while (cp_env[j])
		{
			if (ft_strcmp(cp_env[i], cp_env[j]) > 0)
			{
				temp = cp_env[i];
				cp_env[i] = cp_env[j];
				cp_env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (cp_env);
}

/* -------------------------------------------------------------------------- */

int	print_sorted_env(t_env_vars *env_head)
{
	char		**sorted_env_keys;
	t_env_vars	*env_node;
	int			i;

	sorted_env_keys = get_sorted_env(env_head);
	if (sorted_env_keys == NULL)
		return (-1);
	i = 0;
	while (sorted_env_keys[i])
	{
		env_node = get_env_var(sorted_env_keys[i++], env_head);
		if (env_node == NULL)
			continue ;
		printf("declare -x ");
		if (env_node->key && env_node->value)
			printf("%s=\"%s\"\n", env_node->key, env_node->value);
		else if(env_node->key && !env_node->value)
			printf("%s\n", env_node->key);
	}
	free(sorted_env_keys);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	export_cmd(char **input, t_env_vars *env_head)
{
	t_env_vars	**tracer;
	t_env_vars	*node;
	int			*i;

	node = NULL;
	if (input == NULL)
		return (print_sorted_env(env_head));
	tracer = &env_head;
	while ((*tracer)->next)
		tracer = &(*tracer)->next;
	i = 1;
	while (input[i])
	{
		node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
		if (!node || init_node(input[i++], &env_head) != 0)
			return (free(node), -1);
		(*tracer)->next = node;
	}
	return (0);
}

/* -------------------------------------------------------------------------- */