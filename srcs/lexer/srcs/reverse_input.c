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

void	check_rev(t_reverse *rev, t_info *info)
{
	if (rev->k != 0)
	{
		remp_bef_aft_pipe(info, rev->bef_pipe, rev->aft_pipe, rev->k);
		rev->ptr = info->input;
		info->input = ft_strjoin(rev->bef_pipe, rev->word);
		free(rev->ptr);
		rev->ptr = info->input;
		info->input = ft_strjoin(info->input, rev->aft_pipe);
		free(rev->ptr);
	}
	else
	{
		rev->ptr = info->input;
		info->input = ft_strjoin(rev->word, info->input);
		free(rev->ptr);
	}
}

/* -------------------------------------------------------------------------- */

int	not_operator(t_info *info, int i)
{
	if (info->input[i] != PIPE && info->input[i] != IN && \
		info->input[i] != OUT && info->input[i] != APPEND && \
		info->input[i] != HEREDOC && info->input[i] != ' ')
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	init_rev(t_reverse *rev)
{
	rev->i = 0;
	rev->k = 0;
	rev->start = 0;
	ft_bzero(rev->word, 100);
	ft_bzero(rev->bef_pipe, 500);
	ft_bzero(rev->aft_pipe, 500);
}

/* -------------------------------------------------------------------------- */

void	reverse_input(t_info *info)
{
	t_reverse	rev;

	rev.word = (char *)malloc(100);
	rev.bef_pipe = (char *)malloc(500);
	rev.aft_pipe = (char *)malloc(500);
	init_rev(&rev);
	while (info->input[rev.i])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if ((info->input[rev.i] == IN || info->input[rev.i] == OUT || \
			info->input[rev.i] == APPEND || info->input[rev.i] == HEREDOC) && \
			rev.i != 0)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 100);
			ft_bzero(rev.bef_pipe, 500);
			ft_bzero(rev.aft_pipe, 500);
			continue ;
		}
		rev.i++;
	}
	free_reverse(&rev);
}

/* -------------------------------------------------------------------------- */
