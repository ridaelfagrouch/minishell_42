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

/*
	CMD RULES:

	Change the current working directory to directory. If directory is not 
	supplied, the value of the HOME shell variable is used. Any additional 
	arguments following directory are ignored.

	If directory is ‘-’, it is converted to $OLDPWD before the directory 
	change is attempted.

	If ‘-’ is the first argument, and the directory change is successful, 
	the absolute pathname of the new working directory is written to the 
	standard output.

	???????????????????????????????????????????????????????????????????????????
	If the shell variable CDPATH exists, it is used as a search path: each 
	directory name in CDPATH is searched for directory, with alternative 
	directory names in CDPATH separated by a colon (‘:’). If directory begins 
	with a slash, CDPATH is not used.
	???????????????????????????????????????????????????????????????????????????

	The return status is zero if the directory is successfully changed, 
	non-zero otherwise.
*/

/* -------------------------------------------------------------------------- */
