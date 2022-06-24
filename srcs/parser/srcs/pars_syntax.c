/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:52 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:54:15 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

void	removechar(char *str, char chartoremmove)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}

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

void	init_syntax_data(t_syntax *synta)
{
	synta->dq = -1;
	synta->i = 0;
	synta->cout = 0;
}

int	check_syntax2(char *str)
{
	t_syntax	synta;
	t_quote		*quotes;

	quotes = NULL;
	init_syntax_data(&synta);
	while (str[synta.i])
	{
		if (str[synta.i] == '\"' || str[synta.i] == '\'')
			handle_quotes(&quotes, str, synta.i, &synta.dq);
		if (check_special(SPECIAL_, str[synta.i]) != -1 && !quoted(quotes, 0))
		{
			if ((unsigned long)synta.i == (ft_strlen(str) - 1))
				return (printf ("minishell: parse error near! 6\n"), 1);
			synta.check = str[synta.i++];
			if (check_syntax3(str[synta.i], synta.check, &synta.cout))
				return (1);
		}
		else
		{
			synta.cout = 0;
			synta.i++;
		}
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
