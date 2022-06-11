/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:52 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 16:40:32 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

int	check_syntax3(char c, char check, int *count)
{
	if (check_special(SPECIAL_, c) != -1)
	{
		if (check != c)
			return (printf ("minishell: parse error near! 3\n"), 1);
		if (check == c)
		{
			if (check == '|' || check == '&' || check == ';')
				return (printf ("minishell: parse error near! 4\n"), 1);
			(*count)++;
			if (*count == 2)
				return (printf ("minishell: parse error near! 5\n"), 1);
		}
	}
	if (check == '&' && *count == 0)
	{
		printf ("error: syntax!\n");
		return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

void	handle_quotes1(t_quote **quotes, char *quote, int i, int *check)
{
	if (quote[i] == DOUBLEQ && (*check != 0))
		d_quotes(quotes, quote, i, check);
	else if (quote[i] == SINGELQ && (*check != 1))
		s_quotes(quotes, quote, i, check);
}

/* -------------------------------------------------------------------------- */

int	check_syntax2(char *str)
{
	int				i;
	int				cout;
	char			check;
	t_quote			*quotes;
	int				dq;

	quotes = NULL;
	dq = -1;
	i = 0;
	cout = 0;
	while (str[i])
	{
		if (str[i] == DOUBLEQ || str[i] == SINGELQ)
			handle_quotes1(&quotes, str, i, &dq);
		if (check_special(SPECIAL_, str[i]) != -1 && !quoted(quotes, 0))
		{
			check = str[i++];
			if (check_syntax3(str[i], check, &cout))
				return (1);
		}
		else
		{
			cout = 0;
			i++;
		}
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
