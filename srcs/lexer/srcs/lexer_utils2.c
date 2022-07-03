/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:50:06 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/07/03 01:40:51 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

char	*replaceword(char *s, char *old, char *new)
{
	t_expand	expd;

	expd.i = 0;
	expd.check = 0;
	expd.cnt = 0;
	expd.newlen = ft_strlen((const char *)new);
	expd.oldlen = ft_strlen((const char *)old);
	while (s[expd.i])
	{
		if (ft_strstr(&s[expd.i], old) == &s[expd.i])
		{
			expd.cnt++;
			expd.i += expd.oldlen - 1;
		}
		expd.i++;
	}
	expd.result = (char *) \
		malloc(expd.i + expd.cnt * (expd.newlen - expd.oldlen) + 1);
	expd.i = 0;
	expanding(&expd, s, old, new);
	free(s);
	return (expd.result);
}

/* -------------------------------------------------------------------------- */

void	removechar2(char *str, char chartoremmove, int k)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove && i == k)
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

char	*remove_red_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == IN && str[i + 1] == OUT)
		{
			removechar2(str, str[i + 1], i + 1);
			remove_red_in(str);
		}
		i++;
	}
	return (str);
}
