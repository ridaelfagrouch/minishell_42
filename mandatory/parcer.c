/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:53 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/28 04:31:56 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* ************************************************************************** */

int	check_syntax1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_special(SPECIAL_, str[i]) != -1 && str[i + 1] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (check_special(SPECIAL_, str[i]) != -1)
				return (printf ("minishell: parse error near!\n"), 1);
		}
		else
			i++;
	}
	return (0);
}

/* ************************************************************************** */

int	check_syntax3(char c, char check, int *count)
{
	if (check_special(SPECIAL_, c) != -1)
	{
		if (check != c)
			return (printf ("minishell: parse error near!\n"), 1);
		if (check == c)
		{
			(*count)++;
			if (*count == 2)
				return (printf ("minishell: parse error near!\n"), 1);
		}
	}
	if (check == '&' && *count == 0)
	{
		printf ("error: syntax!\n");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */

int	check_syntax2(char *str)
{
	int		i;
	int		cout;
	char	check;

	i = 0;
	cout = 0;
	while (str[i])
	{
		if (check_special(SPECIAL_, str[i]) != -1)
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

/* ************************************************************************** */

int	parcer(char *str, t_info *info)
{
	t_erreur	isexit;

	(void)info;
	isexit = check_syntax1(str);
	if (isexit == yes || !ft_strcmp(str, "\0"))
		return (free (str), 1);
	isexit = check_syntax2(str);
	if (isexit == yes || !ft_strcmp(str, "\0"))
		return (free (str), 1);
	return (0);
}
