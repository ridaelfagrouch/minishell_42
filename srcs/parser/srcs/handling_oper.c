/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:27:49 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/21 18:12:44 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

void	handel_pipe(t_info *info, t_cmds *cmds)
{
	cmds->token = PIPE;
	cmds->data = NULL;
	cmds->path = NULL;
	cmds->file_fd = -1;
	add_back(&info->head, new_node(cmds));
}

/* -------------------------------------------------------------------------- */

void	handel_in(t_info *info, t_cmds *cmds, char *str)
{
	info->i++;
	scape_space(info);
	while_operator(info, str);
	if (access(str, F_OK) != 0)
	{
		printf("no such file or directory!\n");
		exit(1);
	}
	if (access(str, R_OK | F_OK) == 0)
	{
		cmds->data = ft_strdup(str);
		cmds->file_fd = open(cmds->data, O_RDONLY, 00500);
	}
	cmds->token = IN;
	cmds->path = NULL;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
}

/* -------------------------------------------------------------------------- */

void	handel_herdoc(t_info *info, t_cmds *cmds, char *str)
{
	info->i += 2;
	scape_space(info);
	while_operator(info, str);
	if (str && *str)
		cmds->data = ft_strdup(str);
	else
		cmds->data = NULL;
	cmds->token = HAREDOC;
	cmds->path = NULL;
	cmds->file_fd = -1;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
}

/* -------------------------------------------------------------------------- */

void	handel_out(t_info *info, t_cmds *cmds, char *str)
{
	int	i;

	i = 0;
	if (info->input[info->i] == APPEND)
	{
		info->i += 2;
		i++;
	}
	else
		info->i++;
	scape_space(info);
	while_operator(info, str);
	out_check_str(str, i, cmds);
	cmds->path = NULL;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
}

/* -------------------------------------------------------------------------- */

char *check_str_cmd(char *str)
{
	char	**split;
	char	*cmd;

	split = ft_split(str, ' ');
	cmd = ft_strdup(split[0]);
	free_split(split);
	return(cmd);
}

int	handel_command(t_info *info, t_cmds *cmds, char *str)
{
	int		j;

	j = 0;
	scape_space(info);
	while (info->input[info->i] && check_operator(info, 1))
	{
		str[j] = info->input[info->i];
		info->i++;
		j++;
	}
	cmds->token = COMMAND;
	cmds->file_fd = -1;
	cmds->data = ft_strdup(str);
	if (check_builtins(check_str_cmd(str)) == 0)
	{
		cmds->path = get_path(str);
		if (cmds->path == NULL)
			return (1);
	}
	else
		cmds->path = NULL;
	ft_bzero(str, 50);
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
	return (0);
}

/* -------------------------------------------------------------------------- */
