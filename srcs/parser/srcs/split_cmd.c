/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:47:20 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/14 16:59:09 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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

char	*remove_dq_sq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			removechar(str, str[i]);
			remove_dq_sq(str);
		}
		i++;
	}
	return (str);
}

/* -------------------------------------------------------------------------- */

static char	**ft_creat(char *s, char **result, int row)
{
	int				j;
	size_t			len;
	int				i;
	unsigned int	start;

	j = -1;
	i = 0;
	start = 0;
	while (++j < row)
	{
		len = 0;
		while (s[i] && s[i] != SPACE)
		{
			len++;
			i++;
		}
		result[j] = ft_substr(s, start, len);
		while (s[i] == SPACE)
			i++;
		start = i;
	}
	free(s);
	return (result);
}

/* -------------------------------------------------------------------------- */

static int	str_row(char *tmp)
{
	int	count;

	count = 0;
	while (*tmp)
	{
		if (*tmp == SPACE)
		{
			count++;
			while (*tmp == SPACE)
				tmp++;
		}
		else
			tmp++;
	}
	return (count);
}

/* -------------------------------------------------------------------------- */

char	*ft_space(char *str)
{
	t_quote	*quotes;
	int		i;
	int		check;

	quotes = NULL;
	check = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(&quotes, str, i, &check);
		else if (str[i] == ' ' && !quoted(quotes, 0))
			str[i] = SPACE;
	}
	return (str);
}

/* -------------------------------------------------------------------------- */

char	**ft_split_cmd(char *str)
{
	char	**result ;
	char	*tmp ;
	char	*tmp1;
	int		count;

	result = NULL;
	if (!str)
		return (NULL);
	tmp1 = ft_strtrim(str, " ");
	tmp = remove_dq_sq(ft_space(tmp1));
	count = str_row(tmp);
	if (*str)
		count++;
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	result[count] = NULL;
	return (ft_creat(tmp, result, count));
}

/* -------------------------------------------------------------------------- */
