/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

void	exit_error(char *varname, char *message)
{
	write(2, varname, ft_strlen(varname));
	write(2, ":\t", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

/* -------------------------------------------------------------------------- */

void	exit_cmd(char **input, t_env_vars *env_head)
{
	int8_t	exit_status;
	int		i;

	i = 0;
	while (input[1][i])
	{
		if (!ft_isdigit(input[1][i++]))
		{
			exit_error(input[1], "numeric argument required");
			exit(-1);
		}
	}
	exit_status = ft_atoi(input[1]);
	exit(exit_status);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	Exit the shell, returning a status of n to the shell’s parent. If n is
	omitted, the exit status is that of the last command executed. Any trap
	on EXIT is executed before the shell terminates.
*/

/* -------------------------------------------------------------------------- */
