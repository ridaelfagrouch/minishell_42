/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:51:41 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:52:44 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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

int	condition_valid(t_reverse rev, t_info *info, char *word)
{
	if (rev.j == ft_strlen(word) && (info->input[rev.i + 1] == ' ' || \
		info->input[rev.i + 1] == PIPE || info->input[rev.i + 1] == IN || \
		info->input[rev.i + 1] == OUT || \
		info->input[rev.i + 1] == HAREDOC || \
		info->input[rev.i + 1] == APPEND || info->input[rev.i + 1] == '\0'))
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	delete_word(t_info *info, char *word, size_t start)
{
	t_reverse	rev;

	rev.ls = ft_strlen(info->input);
	rev.lw = ft_strlen(word);
	rev.i = start;
	rev.j = 0;
	printf("hello\n");
	while (rev.i < rev.ls)
	{
		rev.t = rev.i;
		while (rev.j < rev.lw)
		{
			if (info->input[rev.i] == word[rev.j])
				rev.i++;
			rev.j++;
		}
		rev.k = rev.i - rev.t;
		if (rev.k == rev.lw)
		{
			rev.i = rev.t;
			rev.j = rev.i;
			while (info->input[rev.j] && rev.j < (rev.ls - rev.lw))
			{
				info->input[rev.j] = info->input[rev.j + rev.lw];
				rev.j++;
			}
			rev.ls = rev.ls - rev.lw;
			info->input[rev.j] = '\0';
			break ;
		}
		rev.i++;
	}
}

/* -------------------------------------------------------------------------- */

void	set_rev(t_reverse *rev, t_info *info)
{
	rev->j = 0;
	if (info->input[rev->i] == IN || info->input[rev->i] == OUT)
		rev->word[rev->j++] = info->input[rev->i++];
	else if (info->input[rev->i] == APPEND || info->input[rev->i] == HAREDOC)
	{
		rev->word[rev->j++] = info->input[rev->i++];
		rev->word[rev->j++] = info->input[rev->i++];
	}
	while (info->input[rev->i] == ' ')
		rev->word[rev->j++] = info->input[rev->i++];
	while (info->input[rev->i] && not_operator(info, rev->i))
		rev->word[rev->j++] = info->input[rev->i++];
	delete_word(info, rev->word, rev->start);
	rev->word[rev->j] = ' ';
}

/* -------------------------------------------------------------------------- */
