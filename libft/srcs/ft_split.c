/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:50:09 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/09 17:43:04 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

static	void	cal_words_n_repl(char *s, size_t s_len, char c, size_t *words)
{
	size_t	i;

	i = 0;
	while (i < s_len)
	{
		if (s[i] == c)
		{
			s[i] = 0;
			if (s[i + 1] != c)
				*words += 1;
		}
		++i;
	}
}

/* -------------------------------------------------------------------------- */

static	void	free_mem(char **ptr_arr, size_t wrds)
{
	size_t	i;

	i = 0;
	while (i < wrds)
		free(ptr_arr[i++]);
	free(ptr_arr);
}

/* -------------------------------------------------------------------------- */

static	char	**alloc_str(const char *s, size_t wrds, size_t len, char **ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < wrds)
	{
		ptr[i] = ft_strdup(&s[j]);
		if (ptr == NULL)
			return (free_mem(ptr, wrds), (char **)ft_calloc(1, sizeof(char *)));
		while (j < len)
		{
			if (s[j + 1] && !s[j])
			{
				j++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (ptr);
}

/* -------------------------------------------------------------------------- */

char	**ft_split(char const *s, char c)
{
	char	c_to_str[2];
	char	*trim_s;
	size_t	trim_s_len;
	size_t	words;
	char	**ptr_arr;

	c_to_str[0] = c;
	c_to_str[1] = '\0';
	trim_s = ft_strtrim(s, c_to_str);
	if (s == NULL || !(*s) || trim_s == NULL || !(*trim_s))
		return (free(trim_s), (char **)ft_calloc(1, sizeof(char *)));
	trim_s_len = ft_strlen(trim_s);
	words = 1;
	cal_words_n_repl(trim_s, trim_s_len, c, &words);
	ptr_arr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (ptr_arr == NULL)
		return (0);
	ptr_arr = alloc_str((const char *)trim_s, words, trim_s_len, ptr_arr);
	free(trim_s);
	return (ptr_arr);
}

/* -------------------------------------------------------------------------- */
