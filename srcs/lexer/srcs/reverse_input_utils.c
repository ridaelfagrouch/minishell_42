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

void	init_check_text(t_replace *rep, char *text, char *old, char *new)
{
	rep->len1 = ft_strlen(new);
	rep->len2 = ft_strlen(old);
	rep->k = 0;
	rep->i = 0;
	rep->cnt = 0;
	while (text[rep->i])
	{
		if (ft_strstr(&text[rep->i], old) == &text[rep->i])
		{
			rep->cnt++;
			rep->i += rep->len2 - 1;
		}
		rep->i++;
	}
}

/* -------------------------------------------------------------------------- */

char	*replaceword2(char *text, char *old, char *new, int start)
{
	t_replace	rep;

	init_check_text(&rep, text, old, new);
	rep.newstring = (char *) \
		ft_calloc((rep.i + rep.cnt * (rep.len1 - rep.len2) + 1), sizeof(char));
	rep.i = 0;
	while (*text && (rep.i < start))
		rep.newstring[rep.i++] = *text++;
	while (*text)
	{
		if (ft_strstr(text, old) == text && (rep.k == 0))
		{
			ft_strcpy(&rep.newstring[rep.i], new);
			rep.i += rep.len1;
			text += rep.len2;
			rep.k = 1;
		}
		else
			rep.newstring[rep.i++] = *text++;
	}
	rep.newstring[rep.i] = '\0';
	return (rep.newstring);
}

/* -------------------------------------------------------------------------- */

void	set_rev(t_reverse *rev, t_info *info)
{
	rev->j = 0;
	rev->start = rev->i;
	if (info->input[rev->i] == IN || info->input[rev->i] == OUT)
		rev->word[rev->j++] = info->input[rev->i++];
	else if (info->input[rev->i] == APPEND || info->input[rev->i] == HEREDOC)
	{
		rev->word[rev->j++] = info->input[rev->i++];
		rev->word[rev->j++] = info->input[rev->i++];
	}
	while (info->input[rev->i] == ' ')
		rev->word[rev->j++] = info->input[rev->i++];
	while (info->input[rev->i] && not_operator(info, rev->i))
		rev->word[rev->j++] = info->input[rev->i++];
	info->input = replaceword2(info->input, rev->word, "", rev->start);
	rev->word[rev->j] = ' ';
}
