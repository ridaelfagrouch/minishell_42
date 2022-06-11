/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:14:56 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 18:06:48 by rel-fagr         ###   ########.fr       */
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
	char		*result;
	size_t		i;
	size_t		cnt;
	size_t		newlen;
	size_t		oldlen;

	i = 0;
	cnt = 0;
	newlen = ft_strlen((const char *)new);
	oldlen = ft_strlen((const char *)old);
	while (s[i])
	{
		if (strstr(&s[i], old) == &s[i])
		{
			cnt++;
			i += oldlen - 1;
		}
		i++;
	}
	result = (char *)malloc(i + cnt * (newlen - oldlen) + 1);
	i = 0;
	while (*s)
	{
		if (strstr(s, old) == s)
		{
			strcpy(&result[i], new);
			i += newlen;
			s += oldlen;
		}
		else
		result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
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
				&& info->input[info->i] != '\"')
				str[i++] = info->input[info->i++];
			ptr = info->input;
			info->input = ft_strdup(replaceWord(info->input, str, getenv(ft_strtrim(str, "$"))));
			free(ptr);
			ft_bzero(str, 50);
			input_expand(info);
		}
		info->i++;
	}
	return (info->input);
}
