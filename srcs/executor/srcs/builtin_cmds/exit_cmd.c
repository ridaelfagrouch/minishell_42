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

int	exit_cmd(char **input, t_env_vars *env_head)
{
	int8_t	exit_status;

	//exit_status = ft_atoi()
	// if input false, exit with -1 and display error message
	// exit(0);
	return (0);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	Exit the shell, returning a status of n to the shell’s parent. If n is
	omitted, the exit status is that of the last command executed. Any trap
	on EXIT is executed before the shell terminates.
*/

/* -------------------------------------------------------------------------- */
