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

char	*replaceword2(char *text, char *old, char *new, int start) 
{
	int		i;
	int		cnt;
	int		len1;
	int		len2;
	int		k;
	char	*newstring;

	len1 = strlen(new);
	len2 = strlen(old);
	k = 0;
	i = 0;
	cnt = 0;
	while (text[i])
	{
		if (ft_strstr(&text[i], old) == &text[i]) 
		{
			cnt++;
			i += len2 - 1;
		}
		i++;
	}
	newstring = (char *)malloc(i + cnt * (len1 - len2) + 1);
	i = 0;
	while (text[i] && (i < start))
	{
		newstring[i] = text[i];
		i++;
	}
	i = 0;
	while (*text)
	{
		if (ft_strstr(text, old) == text && (k == 0))
		{
			ft_strcpy(&newstring[i], new);
			i += len1;
			text += len2;
			k = 1;
		}
		else
			newstring[i++] = *text++;
	}
	newstring[i] = '\0';
	return (newstring);
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
