/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:53 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 13:42:26 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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

int	check_beginning(char *str, int i)
{
	if (check_special(SPECIAL_, str[i]) != -1 && i == 0)
	{
		if (str[i] == '|')
			return (printf ("minishell: parse error near! 2\n"), 1);
		if (ft_strlen(str) == 1)
			return (printf ("minishell: parse error near! 2\n"), 1);
		if (check_special(SPECIAL_, str[i + 1]) != -1 && ft_strlen(str) == 1)
			return (printf ("minishell: parse error near! 2\n"), 1);
	}
	return (0);
}

int	check_syntax1(char *str)
{
	unsigned long	i;
	t_quote			*quotes;
	int				dq;

	quotes = NULL;
	dq = -1;
	i = 0;
	while (str[i])
	{
		if (check_beginning(str, i))
			return (1);
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(&quotes, str, i, &dq);
		if (check_special(SPECIAL_, str[i]) != -1 && str[i] != '|' && \
			str[i + 1] == ' ' && !quoted(quotes, 0))
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (check_special(SPECIAL_, str[i]) != -1)
				return (printf ("minishell: parse error near! 1\n"), 1);
		}
		else
			i++;
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	parcer(char *str, t_info *info)
{
	if (check_syntax1(str) || !ft_strcmp(str, "\0"))
		return (1);
	if (check_syntax2(str) || !ft_strcmp(str, "\0"))
		return (1);
	if (store_data(info))
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */
