/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mian.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:30:02 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/23 21:30:04 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_info *info)
{
	while (1)
	{
		info->input = readline("\033[0;32m minishell> \033[0m");
		if (!info->input)
		{
			printf("Exit readline\n");
			exit(1);
		}
		add_history(info->input);
		if (lexer_start(info) == 0)
			continue ;
		// if (parcer(ptr))
		// 	return (1);
		free(info->input);
	}
	return (0);
}

/* ************************************************************************** */

int	main(int ac, char **av)
{
	t_info	info;

	if (ft_strcmp(av[0], "./minishell") == 0 && ac == 1)
		if (prompt(&info))
			return (0);
	return (0);
}
