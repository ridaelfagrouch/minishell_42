/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:16:35 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/03 18:44:10 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tc_dst;
	char	*tc_src;
	size_t	i;

	tc_dst = (char *) dst;
	tc_src = (char *) src;
	if (!tc_dst && !tc_src)
		return (NULL);
	if (tc_src > tc_dst)
		ft_memcpy(dst, src, len);
	else if (tc_src < tc_dst)
	{
		i = len;
		while (i-- > 0)
			tc_dst[i] = tc_src[i];
	}
	return (dst);
}

/* -------------------------------------------------------------------------- */
