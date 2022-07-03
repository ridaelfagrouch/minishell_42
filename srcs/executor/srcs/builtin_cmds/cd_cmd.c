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

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

static char	*parse_cd_input(char **input, t_env_vars *env_head)
{
	char		*output;
	t_env_vars	*node;

	output = NULL;
	// printf();
	if (input[1] == NULL)
	{
		node = get_env_var("HOME", env_head);
		if(!node)
			return NULL;
		output = ft_strdup(node->value);
	}	
	else if (ft_strcmp(input[1], "-") == 0)
	{
		node = get_env_var("OLDPWD", env_head);
		output = ft_strdup(node->value);
	}
	else
		output = ft_strdup(input[1]);
	return (output);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

static int	update_old_pwd(t_env_vars **env_head)
{
	char		cwd[PATH_MAX];
	char		*old_wd;
	t_env_vars	*env_node;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err("cd", "error retrieving current directory: getcwd:", \
			"cannot access parent directories: No such file or directory"), -1);
	old_wd = ft_strdup(cwd);
	env_node = get_env_var("OLDPWD", *env_head);
	if (env_node == NULL)
	{
		if (process_env_var(env_head, "OLDPWD"))
			return (free(old_wd), -1);
		env_node = get_env_var("OLDPWD", *env_head);
	}
	free(env_node->value);
	env_node->value = old_wd;
	return (0);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

static int	update_pwd(t_env_vars *env_head)
{
	char		cwd[PATH_MAX];
	t_env_vars	*node;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	node = get_env_var("PWD", env_head);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(cwd);
	}
	return (0);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	cd_cmd(char **input, t_env_vars **env_head)
{
	char	*path;

	// if (!input[1])
	// 	return ();
	path = parse_cd_input(input, *env_head);
	if (!path)
	{
		printf("HOME not set\n");
		return 1;
	}
	if (chdir(path) != 0)
		return (print_err("cd", "no such file or directory", path), 1);
	free(path);
	if (update_old_pwd(env_head) || update_pwd(*env_head))
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */
