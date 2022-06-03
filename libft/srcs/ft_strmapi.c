/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:59:11 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/11 14:20:20 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out_str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	out_str = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!out_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out_str[i] = f(i, s[i]);
		++i;
	}
	return (out_str);
}

/* -------------------------------------------------------------------------- */
