/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:42:10 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/11 11:45:40 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

static char	*assign_chars(char *str, size_t buff_len, int n)
{
	int		digit;
	size_t	index_limit;

	index_limit = 0;
	if (n < 0)
	{
		n *= -1;
		index_limit = 1;
		str[0] = '-';
	}
	while (buff_len-- > index_limit)
	{
		digit = n % 10;
		str[buff_len] = (char)(digit + 48);
		n = (n - digit) / 10;
	}
	return (str);
}

/* -------------------------------------------------------------------------- */

char	*ft_itoa(int n)
{
	size_t	buff_len;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	buff_len = ft_intlen(n);
	str = (char *)ft_calloc(buff_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (assign_chars(str, buff_len, n));
}

/* -------------------------------------------------------------------------- */
