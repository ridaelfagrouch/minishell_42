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

int	echo_cmd(char **input, t_env_vars **env_head)
{
	int	n_flag;
	int	i;

	(void)env_head;
	n_flag = FALSE;
	i = 1;
	while (input[i] && ft_strstr(input[i], "-n"))
	{
		n_flag = TRUE;
		i++;
	}
	while (input[i])
	{
		if (ft_strcmp(input[i], "$?") == 0)
			printf("%d", (int)g_glob.exit);
		else
			printf("%s", input[i]);
		i++;
		if (input[i])
			printf(" ");
	}
	if (n_flag == FALSE)
		printf("\n");
	return (0);
}

/* -------------------------------------------------------------------------- */
