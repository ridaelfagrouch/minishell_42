/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:52 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/15 14:05:58 by rel-fagr         ###   ########.fr       */
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

void	init_syntax_data(int *dq, int *i, int *cout)
{
	*dq = -1;
	*i = 0;
	*cout = 0;
}

int	check_syntax2(char *str)
{
	int				i;
	int				cout;
	char			check;
	t_quote			*quotes;
	int				dq;

	quotes = NULL;
	init_syntax_data(&dq, &i, &cout);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(&quotes, str, i, &dq);
		if (check_special(SPECIAL_, str[i]) != -1 && !quoted(quotes, 0))
		{
			if ((unsigned long)i == (ft_strlen(str) - 1))
				return (printf ("minishell: parse error near! 6\n"), 1);
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
