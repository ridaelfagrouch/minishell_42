/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:04:48 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/05 11:41:03 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

/* -------------------------------------------------------------------------- */

static size_t	check_len(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			s_out_len;

	i = 0;
	s_out_len = 0;
	while (s[start++] && i++ < len)
		++s_out_len;
	return (s_out_len);
}

/* -------------------------------------------------------------------------- */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*s_out;
	size_t	i;
	size_t	the_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
	{
		s_out = (char *) ft_calloc(1, sizeof(char));
		if (s_out == NULL)
			return (0);
		return (s_out);
	}
	the_len = check_len(s, start, len);
	s_out = (char *) ft_calloc(the_len + 1, sizeof(char));
	if (s_out == NULL)
		return (0);
	i = 0;
	while (s[start] && i < len)
		s_out[i++] = s[start++];
	return (s_out);
}

/* -------------------------------------------------------------------------- */
