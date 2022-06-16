/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 21:37:48 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
	Built-In vs Shell Programs

	Built-in commands are executed as a function.But it may fork first if you 
	use it in a pipeline '|', for example:
		$ cd / | echo 
	it forks and calls cd in the child. You can also notice this by how 
	the directory doesn't actually change.
*/

/* -------------------------------------------------------------------------- */

int	execute_non_builtin(char **input, t_env_vars *head)
{
	input = NULL;
	head = NULL;
	return (0);
}

/* -------------------------------------------------------------------------- */

int	execute_command(char **input, t_env_vars *env_vars)
{
	int		return_value;

	return_value = -1;
	if (input == NULL || *input)
		return (-1);
	else if (ft_strcmp(input[0], "echo"))
		return_value = echo_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "cd"))
		return_value = cd_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "pwd"))
		return_value = pwd_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "export"))
		return_value = export_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "unset"))
		return_value = unset_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "env"))
		return_value = env_cmd(input, env_vars);
	else if (ft_strcmp(input[0], "exit"))
		return_value = exit_cmd(input, env_vars);
	else
		return_value = execute_non_builtin(input, env_vars);
	return (return_value);
}

/* -------------------------------------------------------------------------- */
