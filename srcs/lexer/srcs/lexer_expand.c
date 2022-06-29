/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:14:56 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/18 17:32:26 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	expanding(t_expand *expd, char *s, char *old, char *new)
{
	while (*s)
	{
		if (ft_strstr(s, old) == s && expd->check == 0)
		{
			ft_strcpy(&expd->result[expd->i], new);
			expd->i += expd->newlen;
			s += expd->oldlen;
			expd->check += 1;
		}
		else
		expd->result[expd->i++] = *s++;
	}
	expd->result[expd->i] = '\0';
}

/* -------------------------------------------------------------------------- */

char	*replaceword(char *s, char *old, char *new)
{
	t_expand	expd;

	expd.i = 0;
	expd.check = 0;
	expd.cnt = 0;
	expd.newlen = ft_strlen((const char *)new);
	expd.oldlen = ft_strlen((const char *)old);
	while (s[expd.i])
	{
		if (ft_strstr(&s[expd.i], old) == &s[expd.i])
		{
			expd.cnt++;
			expd.i += expd.oldlen - 1;
		}
		expd.i++;
	}
	expd.result = (char *) \
		malloc(expd.i + expd.cnt * (expd.newlen - expd.oldlen) + 1);
	expd.i = 0;
	expanding(&expd, s, old, new);
	return (expd.result);
}

/* -------------------------------------------------------------------------- */

int	check_expand(t_info *info)
{
	if (info->input[info->i] && info->input[info->i] != ' ' && \
		info->input[info->i] != DQ && info->input[info->i] != SQ \
		&& info->input[info->i] != PIPE && info->input[info->i] != OUT \
		&& info->input[info->i] != IN && info->input[info->i] != EXPAND \
		&& info->input[info->i] != HAREDOC && \
		info->input[info->i] != APPEND)
		return (1);
	else
		return (0);
}

void	get_expand_env(t_info *info, t_expand *expd)
{
	info->input[info->i] = '$';
	if (check_expand(info))
		while (check_expand(info))
			expd->str[expd->i++] = info->input[info->i++];
	else
		expd->str[expd->i] = '$';
	expd->ptr = info->input;
	expd->result = get_env(ft_strtrim(expd->str, "$"), *g_glob.env_head);
}

/* -------------------------------------------------------------------------- */

char	*input_expand(t_info *info)
{
	t_expand	expd;

	info->i = -1;
	expd.i = 0;
	expd.str = (char *)malloc(100);
	ft_bzero(expd.str, 100);
	while (info->input[++(info->i)])
	{
		if (info->input[info->i] == EXPAND)
		{
			get_expand_env(info, &expd);
			if (expd.result == NULL)
			{
				info->input = \
				ft_strdup(replaceword(info->input, expd.str, " "));
				expd.i = 0;
				ft_bzero(expd.str, 100);
				continue ;
			}
			info->input = \
				ft_strdup(replaceword(info->input, expd.str, expd.result));
			free_expand(&expd);
			input_expand(info);
		}
	}
	return (info->input);
}

/* -------------------------------------------------------------------------- */
