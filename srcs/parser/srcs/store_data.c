/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:16:09 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 13:41:35 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

int	check_operator(t_info *info, int flag)
{
	if (flag == 1)
	{
		if (info->input[info->i] && info->input[info->i] != PIPE && \
		info->input[info->i] != OUT && info->input[info->i] != IN && \
		info->input[info->i] != HAREDOC && info->input[info->i] != APPEND)
			return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	operator_statements(t_info *info)
{
	if ((check_operator(info, 1) && info->input[info->i] != ' ') || \
		info->input[info->i] == IN || info->input[info->i] == OUT || \
		info->input[info->i] == APPEND || info->input[info->i] == HAREDOC)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	all_operator(t_info *info, char *str, t_cmds *cmds)
{
	if (check_operator(info, 1) && info->input[info->i] != ' ')
	{
		if (handel_command(info, cmds, str))
			return (1);
	}
	else if (info->input[info->i] == IN)
		handel_in(info, cmds, str);
	else if (info->input[info->i] == OUT || \
		info->input[info->i] == APPEND)
		handel_out(info, cmds, str);
	else if (info->input[info->i] == HAREDOC)
		handel_herdoc(info, cmds, str);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	store_data(t_info *info)
{
	char	*str;
	t_cmds	*cmds;

	info->i = 0;
	info->head = NULL;
	str = (char *)malloc(sizeof(char) * 50);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!str || !cmds)
		exit(1);
	ft_bzero(str, 50);
	while (info->input[info->i])
	{
		if (operator_statements(info))
		{
			if (all_operator(info, str, cmds))
				return (1);
			continue ;
		}
		else if (info->input[info->i] == PIPE)
			handel_pipe(info, cmds);
		info->i++;
	}
	return (0);
}
