/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:16:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/23 20:15:32 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	while_operator(t_info *info, char *str)
{
	int	j;

	j = 0;
	while (info->input[info->i] && check_operator(info, 1))
		str[j++] = info->input[info->i++];
	remove_dq_sq(str);
	printf("|%s|\n", str);
}

/* -------------------------------------------------------------------------- */

void	scape_space(t_info *info)
{
	while (info->input[info->i] && info->input[info->i] == ' ')
		info->i++;
}

/* -------------------------------------------------------------------------- */

int	check_builtins(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 || \
		ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || \
		ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "ECHO") == 0 || ft_strcmp(str, "CD") == 0 || \
		ft_strcmp(str, "PWD") == 0 || ft_strcmp(str, "EXPORT") == 0 || \
		ft_strcmp(str, "UNSET") == 0 || ft_strcmp(str, "ENV") == 0 || \
		ft_strcmp(str, "EXIT") == 0)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	out_check_str(char *str, int i, t_cmds *cmds)
{
	if (access(str, W_OK) != 0 && access(str, F_OK) == 0)
		printf("minishell: %s: Permission denied\n", str);
	if (str && *str)
	{
		cmds->data = ft_strdup(str);
		if (access(str, F_OK) != 0 && i != 1)
			cmds->file_fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 00774);
		else if (access(str, F_OK) != 0 && i == 1)
			cmds->file_fd = open(str, O_CREAT | O_RDWR | O_APPEND, 00774);
		else if (access(str, F_OK) == 0 && i != 1)
			cmds->file_fd = open(str, O_RDWR | O_TRUNC, 00774);
		else if (access(str, F_OK) == 0 && i == 1)
			cmds->file_fd = open(str, O_RDWR | O_APPEND, 00774);
	}
	else
		cmds->data = NULL;
	if (i == 1)
		cmds->token = APPEND;
	else
		cmds->token = OUT;
}

/* -------------------------------------------------------------------------- */