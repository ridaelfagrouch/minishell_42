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
	if (input == NULL || *input)
		return (-1);
	else if (ft_strcmp(input[0], "echo"))
		return (echo_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "cd"))
		return (cd_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "pwd"))
		return (pwd_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "export"))
		return (export_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "unset"))
		return (unset_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "env"))
		return (env_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "exit"))
		return(exit_cmd(input, env_vars), 0);
	return (execute_non_builtin(input, env_vars));
}

/* -------------------------------------------------------------------------- */
