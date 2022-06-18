/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:02:51 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/18 15:30:50 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

int	check_special(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			if (str[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

/* -------------------------------------------------------------------------- */

void	delete_word(t_info *info, char *word)
{
	t_reverse	rev;

	rev.i = 0;
	rev.j = 0;
	while (rev.i < ft_strlen(info->input))
	{
		if (info->input[rev.i] == word[rev.j])
			rev.j++;
		else
			rev.j = 0;
		if (rev.j == ft_strlen(word))
		{
			rev.t = 0;
			while (rev.t <= ft_strlen(word))
			{
				rev.k = 0;
				while (rev.k < ft_strlen(info->input))
				{
					info->input[rev.i - rev.j + rev.k] = \
						info->input[rev.i - rev.j + rev.k + 1];
					rev.k++;
				}
				rev.t++;
			}
		}
		rev.i++;
	}
}

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

void	remp_bef_aft_pipe(t_info *info, char *bef_pipe, char *aft_pipe, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->input[i] && i <= k)
		bef_pipe[j++] = info->input[i++];
	j = 0;
	while (info->input[i])
		aft_pipe[j++] = info->input[i++];
}

/* -------------------------------------------------------------------------- */

void	init_rev(t_reverse *rev)
{
	rev->i = 0;
	rev->k = -1;
	rev->k = 0;
	ft_bzero(rev->word, 50);
	ft_bzero(rev->bef_pipe, 50);
	ft_bzero(rev->aft_pipe, 50);
}

/* -------------------------------------------------------------------------- */

void	set_rev(t_reverse *rev, t_info *info)
{
	rev->j = 0;
	if (info->input[rev->i] == IN || info->input[rev->i] == OUT)
		rev->word[rev->j++] = info->input[rev->i++];
	else if (info->input[rev->i] == APPEND)
	{
		rev->word[rev->j++] = info->input[rev->i++];
		rev->word[rev->j++] = info->input[rev->i++];
	}
	while (info->input[rev->i] == ' ')
		rev->word[rev->j++] = info->input[rev->i++];
	while (info->input[rev->i] && not_operator(info, rev->i))
		rev->word[rev->j++] = info->input[rev->i++];
	delete_word(info, rev->word);
	rev->word[rev->j] = ' ';
	rev->ptr = info->input;
}

/* -------------------------------------------------------------------------- */

void	check_rev(t_reverse *rev, t_info *info)
{
	if (rev->k != 0)
	{
		remp_bef_aft_pipe(info, rev->bef_pipe, rev->aft_pipe, rev->k);
		info->input = ft_strjoin(rev->bef_pipe, rev->word);
		free(rev->ptr);
		rev->ptr = info->input;
		info->input = ft_strjoin(info->input, rev->aft_pipe);
	}
	else
		info->input = ft_strjoin(rev->word, info->input);
}

/* -------------------------------------------------------------------------- */

void	reverse_input(t_info *info)
{
	t_reverse	rev;

	rev.word = (char *)malloc(50);
	rev.bef_pipe = (char *)malloc(50);
	rev.aft_pipe = (char *)malloc(50);
	init_rev(&rev);
	while (info->input[rev.i])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if (info->input[rev.i] == IN || info->input[rev.i] == OUT || \
			info->input[rev.i] == APPEND)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 50);
			ft_bzero(rev.bef_pipe, 50);
			ft_bzero(rev.aft_pipe, 50);
			free(rev.ptr);
			continue ;
		}
		rev.i++;
	}
	printf("|%s|\n", info->input);
	free(rev.word);
}

/* -------------------------------------------------------------------------- */
