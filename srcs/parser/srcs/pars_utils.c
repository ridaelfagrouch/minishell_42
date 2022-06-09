/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:16:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/09 15:37:10 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	while_operator(t_info *info, char *str)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	if (info->input[info->i] == DOUBLEQ || info->input[info->i] == SINGELQ)
	{
		while (info->input[info->i] == DOUBLEQ || info->input[info->i] == SINGELQ)
			info->i++;
		while (info->input[info->i] != DOUBLEQ && info->input[info->i] != SINGELQ)
		{
			str[j] = info->input[info->i];
			info->i++;
			j++;
		}
		while (info->input[info->i] == DOUBLEQ || info->input[info->i] == SINGELQ)
			info->i++;
	}
	else
	{
		while (info->input[info->i] && check_operator(info, 1) \
			&& info->input[info->i] != ' ')
		{
			while (info->input[info->i] == DOUBLEQ || \
				info->input[info->i] == SINGELQ)
				info->i++;
			str[j] = info->input[info->i];
			info->i++;
			j++;
		}
	}
}

/* -------------------------------------------------------------------------- */

void	scape_space(t_info *info)
{
	while (info->input[info->i] && info->input[info->i] == ' ')
		info->i++;
}

/* -------------------------------------------------------------------------- */
