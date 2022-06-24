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

u_int8_t	ascii_to_8bit_int(const char *str)
{
	int8_t		sign;
	u_int8_t	sum;
	int			i;

	i = 0;
	sum = 0;
	sign = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
		sign = str[i] - '+';
	while (ft_isdigit(str[i]))
		sum = (sum * 10) + (str[i++] - '0');
	if (sign)
		sum *= -1;
	return (sum);
}

/* -------------------------------------------------------------------------- */

void	exit_cmd(char **input, t_env_vars **env_head)
{
	u_int8_t	exit_status;
	int			i;

	(void)env_head;
	i = 0;
	exit_status = g_glob.exit;
	if (input[1])
	{
		while (input[1][i])
		{
			if (!ft_isdigit(input[1][i++]))
			{
				exit_error(input[1], "numeric argument required");
				exit(-1);
			}
		}
		exit_status = ascii_to_8bit_int(input[1]);
	}
	exit((int)exit_status);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	Exit the shell, returning a status of n to the shell’s parent. If n is
	omitted, the exit status is that of the last command executed. Any trap
	on EXIT is executed before the shell terminates.
*/

/* -------------------------------------------------------------------------- */
