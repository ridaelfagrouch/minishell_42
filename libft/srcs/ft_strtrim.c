/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:21:21 by mnaimi            #+#    #+#             */
/*   Updated: 2021/11/09 10:00:51 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* -------------------------------------------------------------------------- */

static char	*move_chars(const char *set, char *s1_ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (set[i] && *s1_ptr)
	{
		j = ft_strlen(s1_ptr) - 1;
		if (set[i] == s1_ptr[0])
		{
			s1_ptr++;
			i = 0;
		}
		else if (set[i] == s1_ptr[j])
		{
			s1_ptr[j--] = 0;
			i = 0;
		}
		else
			i++;
	}
	return (s1_ptr);
}

/* -------------------------------------------------------------------------- */

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_ptr;
	char	*s1_ptr_cpd;
	char	*final_str;

	if (!s1 || !set)
		return (NULL);
	s1_ptr = ft_strdup(s1);
	if (s1_ptr == NULL)
		return (NULL);
	s1_ptr_cpd = s1_ptr;
	final_str = ft_strdup((const char *)(move_chars(set, s1_ptr)));
	if (final_str == NULL)
		return (NULL);
	free(s1_ptr_cpd);
	return (final_str);
}

/* -------------------------------------------------------------------------- */
