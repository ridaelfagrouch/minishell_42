/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leakser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:41 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/28 04:31:43 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_quote(t_quote **quotes, int i, int on, int class)
{
	t_quote	*quote;
	t_quote	*tmp;

	quote = malloc(sizeof(t_quote) * 1);
	quote->i = i;
	if (on >= 0)
		quote->on = 1;
	else
		quote->on = 0;
	quote->class = class;
	quote->next = NULL;
	if (!*quotes)
		*quotes = quote;
	else
	{
		tmp = *quotes;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = quote;
	}
}

/* ************************************************************************** */

int	quoted(t_quote *quotes, int i)
{
	t_quote	*tmp;

	if (!quotes)
		return (0);
	tmp = quotes;
	while (tmp->next)
		tmp = tmp->next;
	if (i)
		if (tmp->on == 1 && tmp->class == 1)
			return (0);
	if (tmp->on == 0)
		return (0);
	return (1);
}

/* ************************************************************************** */

void	unclosed_quotes(t_quote *quotes, t_info *info)
{
	if (quoted(quotes, 0))
	{
		printf("Unclosed quotes!\n");
		info->uncqu = 1;
	}
}

/* ************************************************************************** */

int	check_dolar(t_info *info, int i, t_quote *quotes)
{
	return (info->input[i] == '$' && info->input[i + 1]
		&& (ft_isalnum(info->input[i + 1])
			|| info->input[i + 1] == '?'
			|| info->input[i + 1] == '_') && !quoted(quotes, 1));
}

/* ************************************************************************** */

void	d_quotes(t_quote **quotes, char *input, int i, int *check)
{
	if (*check == 1)
		*check = -1;
	else if (*check == -1)
		*check = 1;
	new_quote(quotes, i, *check, 1);
	input[i] = DOUBLEQ;
}

/* ************************************************************************** */

void	s_quotes(t_quote **quotes, char *input, int i, int *check)
{
	if (*check == 0)
		*check = -1;
	else if (*check == -1)
		*check = 0;
	new_quote(quotes, i, *check, 0);
	input[i] = SINGELQ;
}

/* ************************************************************************** */

void	handle_quotes(t_quote **quotes, char *quote, int i, int *check)
{
	if (quote[i] == '\"' && (*check != 0))
		d_quotes(quotes, quote, i, check);
	else if (quote[i] == '\'' && (*check != 1))
		s_quotes(quotes, quote, i, check);
}

/* ************************************************************************** */

void	in_out(char *input, int *i, t_quote	*quotes)
{
	if (input[*i] == '<' && !quoted(quotes, 0))
	{
		if (input[*i + 1] == '<')
		{
			(*i)++;
			input[*i] = HAREDOC;
		}
		else
			input[*i] = IN;
	}
	else if (input[*i] == '>' && !quoted(quotes, 0))
	{
		if (input[*i + 1] == '>')
		{
			(*i)++;
			input[*i] = APPEND;
		}
		input[*i] = OUT;
	}
}

/* ************************************************************************** */

t_quote	*check_input(t_info *info)
{
	t_quote	*quotes;
	int		i;
	int		dq;

	quotes = NULL;
	dq = -1;
	i = -1;
	while (info->input[++i])
	{
		if (info->input[i] == '\"' || info->input[i] == '\'')
			handle_quotes(&quotes, info->input, i, &dq);
		else if (info->input[i] == '|' && !quoted(quotes, 0))
			info->input[i] = PIPE;
		else if (info->input[i] == ' ' && !quoted(quotes, 0))
			info->input[i] = SPACE;
		else if (info->input[i] == ';' && !quoted(quotes, 0))
			info->input[i] = SEMICOLON;
		else if (check_dolar(info, i, quotes))
			info->input[i] = EXPAND;
		else
			in_out(info->input, &i, quotes);
	}
	unclosed_quotes(quotes, info);
	return (quotes);
}

/* ************************************************************************** */

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

/* ************************************************************************** */

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
