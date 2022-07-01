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
	while (node)
	{
		node = node->next;
		count++;
	}
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
		return (1);
	i = 0;
	while (sorted_env_keys[i])
	{
		env_node = get_env_var(sorted_env_keys[i++], env_head);
		if (env_node == NULL)
			continue ;
		printf("declare -x ");
		if (env_node->key && env_node->value)
			printf("%s=\"%s\"\n", env_node->key, env_node->value);
		else if (env_node->key && !env_node->value)
			printf("%s\n", env_node->key);
	}
	free(sorted_env_keys);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_env_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] && !(key[i] == '+' && key[i + 1] == '=') && key[i] != '=')
	{
		if (i == 0 && !ft_isalpha(key[i]) && key[i] != '_')
			return (1);
		else if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
/* -------------------------------------------------------------------------- */
// TODO OLDPWD not set empty
int	export_cmd(char **env_var, t_env_vars **env_head)
{
	int	i;

	if (env_var[1] == NULL)
		return (print_sorted_env(*env_head));
	i = 1;
	while (env_var[i])
	{
		if (check_env_key(env_var[i]))
			return (print_err("export", env_var[i], "not a valid identifier"), \
				1);
		if (process_env_var(env_head, env_var[i++]))
			return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */