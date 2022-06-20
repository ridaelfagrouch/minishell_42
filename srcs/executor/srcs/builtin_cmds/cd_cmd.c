/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

static char	*parse_cd_input(char **input, t_env_vars *env_head)
{
	char		*output;
	t_env_vars	*node;

	output = NULL;
	if (ft_strlen(input[1]) == 1 && ft_strcmp(input[0], "-") == 0)
	{
		node = get_env_var("OLDPWD", env_head);
		output = ft_strdup(node->value);
	}
	else
		output = ft_strdup(input[1]);
	return (output);
}

/* -------------------------------------------------------------------------- */

static int	update_old_pwd(t_env_vars *env_head)
{
	char 		cwd[PATH_MAX];
	char		*old_wd;
	t_env_vars	*env_node;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	old_wd = ft_strdup(cwd);
	env_node = get_env_var("OLDPWD", env_head);
	if (env_node == NULL)
	{
		if (init_node("OLDPWD", &env_head))
			return (free(old_wd), -1);
		env_node = get_env_var("OLDPWD", env_head);
	}
	free(env_node->value);
	env_node->value = old_wd;
	return (0);
}

/* -------------------------------------------------------------------------- */

static int	update_pwd(t_env_vars *env_head)
{
	char 		cwd[PATH_MAX];
	t_env_vars	*node;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	node = get_env_var("PWD", env_head);
	if (node)
	{
		free(env_head->value);
		env_head->value = ft_strdup(cwd);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	cd_cmd(char **input, t_env_vars *env_head)
{
	char	*path;
	
	path = parse_cd_input(input, env_head);
	if (chdir(path) != 0)
		return (-1);
	free(path);
	if (update_old_pwd(env_head) != 0 || update_pwd(env_head))
		return (-1);
	return (0);
}

/* -------------------------------------------------------------------------- */
