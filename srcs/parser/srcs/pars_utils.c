/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:16:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:57:37 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

char	*check_str_cmd(char *str)
{
	char	**split;
	char	*cmd;

	split = ft_split(str, ' ');
	cmd = ft_strdup(split[0]);
	free_split(split);
	return (cmd);
}

/* -------------------------------------------------------------------------- */

void	while_operator(t_info *info, char *str)
{
	t_quote	*quotes;
	int		check;
	int		j;

	j = 0;
	quotes = NULL;
	check = -1;
	while (info->input[info->i] && check_operator(info, 1))
	{
		if (info->input[info->i] == '\"' || info->input[info->i] == '\'')
			handle_quotes(&quotes, info->input, info->i, &check);
		if (info->input[info->i] == ' ' && !quoted(quotes, 0))
			break ;
		str[j++] = info->input[info->i++];
	}
	remove_dq_sq(str);
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
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++ ;
	}
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 || \
		ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || \
		ft_strcmp(str, "exit") == 0)
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