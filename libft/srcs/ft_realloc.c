/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:10:46 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/09 09:39:16 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(1, new_size);
	if (new_ptr == NULL)
		return (old_ptr);
	new_ptr = ft_memmove(new_ptr, old_ptr, old_size);
	return (free(old_ptr), new_ptr);
}

/* -------------------------------------------------------------------------- */
