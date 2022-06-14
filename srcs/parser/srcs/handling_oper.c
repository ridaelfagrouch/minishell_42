/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:27:49 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/14 12:02:48 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

void	handel_pipe(t_info *info, t_cmds *cmds)
{
	cmds->token = PIPE;
	cmds->data = NULL;
	cmds->path = NULL;
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
		cmds->data = ft_strdup(str);
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
	if (access(str, W_OK) != 0 && access(str, F_OK) == 0)
		printf("minishell: %s: Permission denied\n", str);
	if (str && *str)
	{
		cmds->data = ft_strdup(str);
		if (access(str, F_OK) != 0)
			open(str, O_CREAT | O_RDWR, 00774);
	}
	else
		cmds->data = NULL;
	if (i == 1)
		cmds->token = APPEND;
	else
		cmds->token = OUT;
	cmds->path = NULL;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
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
	cmds->data = ft_strdup(str);
	cmds->path = get_path(str);
	if (cmds->path == NULL)
		return (1);
	ft_bzero(str, 50);
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
	return (0);
}

/* -------------------------------------------------------------------------- */
