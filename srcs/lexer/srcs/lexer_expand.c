/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:14:56 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/07/03 02:25:28 by rel-fagr         ###   ########.fr       */
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

int	check_expand(char *input, int i)
{
	if (input[i] && \
		(ft_isalnum(input[i]) || input[i] == '?' || input[i] == '_') \
		&& input[i] != ' ' && \
		input[i] != DQ && input[i] != SQ \
		&& input[i] != PIPE && input[i] != OUT \
		&& input[i] != IN && input[i] != EXPAND \
		&& input[i] != HEREDOC && \
		input[i] != APPEND)
		return (1);
	else
		return (0);
}

/* -------------------------------------------------------------------------- */

void	get_expand_env(char *input, int *i, t_expand *expd)
{
	char	*ptr;

	expd->i = 0;
	input[*i] = '$';
	expd->str[expd->i] = '$';
	expd->i++;
	(*i)++;
	if (check_expand(input, *i))
	{
		while (check_expand(input, *i))
			expd->str[expd->i++] = input[(*i)++];
	}
	expd->ptr = input;
	ptr = ft_strtrim(expd->str, "$");
	expd->result = ft_strdup(get_env(ptr, *g_glob.env_head));
	free(ptr);
}

/* -------------------------------------------------------------------------- */

void	ft_expand_bzero(t_expand *expd, int *i)
{
	*i = 0;
	ft_bzero(expd->str, 100);
}

char	*input_expand(char *input)
{
	t_expand	expd;
	int			i;

	i = 0;
	expd.str = (char *)malloc(100);
	ft_bzero(expd.str, 100);
	while (input[i])
	{
		if (input[i] == EXPAND)
		{
			get_expand_env(input, &i, &expd);
			if (expd.result == NULL)
			{
				input = replaceword(input, expd.str, "");
				ft_expand_bzero(&expd, &i);
				continue ;
			}
			input = replaceword(input, expd.str, expd.result);
			ft_expand_bzero(&expd, &i);
			free(expd.result);
			continue ;
		}
		i++;
	}
	return (free (expd.str), input);
}

/* -------------------------------------------------------------------------- */
