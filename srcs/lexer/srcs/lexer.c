/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:41 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/23 15:31:18 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	d_quotes(t_quote **quotes, int i, int *check)
{
	if (*check == 1)
		*check = -1;
	else if (*check == -1)
		*check = 1;
	new_quote(quotes, i, *check, 1);
}

/* -------------------------------------------------------------------------- */

void	s_quotes(t_quote **quotes, int i, int *check)
{
	if (*check == 0)
		*check = -1;
	else if (*check == -1)
		*check = 0;
	new_quote(quotes, i, *check, 0);
}

/* -------------------------------------------------------------------------- */

void	handle_quotes(t_quote **quotes, char *quote, int i, int *check)
{
	if (quote[i] == '\"' && (*check != 0))
		d_quotes(quotes, i, check);
	else if (quote[i] == '\'' && (*check != 1))
		s_quotes(quotes, i, check);
}

/* -------------------------------------------------------------------------- */

t_quote	*check_input(t_info *info)
{
	t_quote	*quotes;
	int		i;
	int		check;

	quotes = NULL;
	check = -1;
	i = -1;
	while (info->input[++i])
	{
		if (info->input[i] == '\"' || info->input[i] == '\'')
			handle_quotes(&quotes, info->input, i, &check);
		else if (info->input[i] == '|' && !quoted(quotes, 0))
			info->input[i] = PIPE;
		else if (info->input[i] == ';' && !quoted(quotes, 0))
			info->input[i] = SEMICOLON;
		else if (check_dollar(info, i, quotes))
			info->input[i] = EXPAND;
		else if (!quoted(quotes, 0))
			in_out(info->input, &i, quotes);
	}
	reverse_input(info);
	info->input = ft_strdup(input_expand(info));
	unclosed_quotes(quotes, info);
	return (quotes);
}

/* -------------------------------------------------------------------------- */

int	lexer_start(t_info *info)
{
	t_quote	*quotes;

	quotes = check_input(info);
	if (info->uncqu == 1)
	{
		free_quotes(quotes);
		info->uncqu = 0;
		return (0);
	}
	free_quotes(quotes);
	return (1);
}

/* -------------------------------------------------------------------------- */
