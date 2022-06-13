/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:14:56 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/13 15:17:34 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	free_quotes(t_quote *quotes)
{
	t_quote	*next;

	while (quotes)
	{
		next = quotes->next;
		free(quotes);
		quotes = next;
	}
}

/* -------------------------------------------------------------------------- */

char	*replaceWord(char *s, char *old, char *new)
{
	t_expand exp;

	exp.i = 0;
	exp.cnt = 0;
	exp.newlen = ft_strlen((const char *)new);
	exp.oldlen = ft_strlen((const char *)old);
	while (s[exp.i])
	{
		if (strstr(&s[exp.i], old) == &s[exp.i])
		{
			exp.cnt++;
			exp.i += exp.oldlen - 1;
		}
		exp.i++;
	}
	exp.result = (char *)malloc(exp.i + exp.cnt * (exp.newlen - exp.oldlen) + 1);
	exp.i = 0;
	while (*s)
	{
		if (strstr(s, old) == s && exp.check == 0)
		{
			strcpy(&exp.result[exp.i], new);
			exp.i += exp.newlen;
			s += exp.oldlen;
			exp.check += 1;
		}
		else
		exp.result[exp.i++] = *s++;
	}
	exp.result[exp.i] = '\0';
	return (exp.result);
}

/* -------------------------------------------------------------------------- */

char	*input_expand(t_info *info)
{
	char	*ptr;
	char	*str;
	int		i;	

	info->i = 0;
	i = 0;
	str = (char *)malloc(50);
	ft_bzero(str, 50);
	while (info->input[info->i])
	{
		if (info->input[info->i] == EXPAND)
		{
			info->input[info->i] = '$';
			while (info->input[info->i] && info->input[info->i] != ' ' \
				&& info->input[info->i] != DOUBLEQ)
				str[i++] = info->input[info->i++];
			ptr = info->input;
			info->input = ft_strdup(replaceWord(info->input, str, getenv(ft_strtrim(str, "$"))));
			free(ptr);
			free(str);
			input_expand(info);
		}
		info->i++;
	}
	return (info->input);
}
