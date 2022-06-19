/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

int	echo_cmd(char **input, t_env_vars *env_head)
{
	bool	n_flag;
	int		i;

	(void)env_head;
	n_flag = false;
	if (ft_strstr(input[1], "-n"))
		n_flag = true;
	i = 1;
	while (input[i])
		printf("%s", input[i++]);
	if (n_flag == false)
		printf("\n");
	return (0);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	Output the args, separated by spaces, terminated with a newline. The
	return status is 0 unless a write error occurs. If -n is specified, the
	trailing newline is suppressed.
	The xpg_echo shell option may be used to dynamically determine whether or
	not echo expands these escape characters by default. echo does not
	interpret -- to mean the end of options.
*/

/* -------------------------------------------------------------------------- */
