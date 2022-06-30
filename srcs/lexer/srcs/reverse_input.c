/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:02:51 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:51:31 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

// int	check_special(char *str, int c)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == (char)c)
// 		{
// 			if (str[i + 1] == (char)c)
// 			{
// 				i += 2;
// 				continue ;
// 			}
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

/* -------------------------------------------------------------------------- */

int	not_operator(t_info *info, int i)
{
	if (info->input[i] != PIPE && info->input[i] != IN && \
		info->input[i] != OUT && info->input[i] != APPEND && \
		info->input[i] != HAREDOC && info->input[i] != ' ')
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	init_rev(t_reverse *rev)
{
	rev->i = -1;
	rev->k = 0;
	ft_bzero(rev->word, 50);
	ft_bzero(rev->bef_pipe, 100);
	ft_bzero(rev->aft_pipe, 100);
}

/* -------------------------------------------------------------------------- */

void	reverse_herdoc(t_info *info)
{
	t_reverse	rev;

	info->input = remove_red_in(info->input, 0);
	rev.word = (char *)malloc(50);
	rev.bef_pipe = (char *)malloc(100);
	rev.aft_pipe = (char *)malloc(100);
	init_rev(&rev);
	while (info->input[++(rev.i)])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if (info->input[rev.i] == HAREDOC && rev.i != 0)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 50);
			ft_bzero(rev.bef_pipe, 100);
			ft_bzero(rev.aft_pipe, 100);
			continue ;
		}
	}
	free_reverse(&rev);
}

/* -------------------------------------------------------------------------- */

void	reverse_input(t_info *info)
{
	t_reverse	rev;

	info->input = remove_red_in(info->input, 0);
	rev.word = (char *)malloc(50);
	rev.bef_pipe = (char *)malloc(100);
	rev.aft_pipe = (char *)malloc(100);
	init_rev(&rev);
	while (info->input[++(rev.i)])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if ((info->input[rev.i] == IN || info->input[rev.i] == OUT || \
			info->input[rev.i] == APPEND || info->input[rev.i] == HAREDOC) && \
			rev.i != 0)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 50);
			ft_bzero(rev.bef_pipe, 100);
			ft_bzero(rev.aft_pipe, 100);
			continue ;
		}
	}
	free_reverse(&rev);
	reverse_herdoc(info);
}

/* -------------------------------------------------------------------------- */
