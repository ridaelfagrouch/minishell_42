/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:53 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/28 04:31:56 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

int	check_special(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			if (str[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

/* -------------------------------------------------------------------------- */

int	check_syntax1(char *str)
{
	unsigned long	i;

	i = 0;
	while (str[i])
	{
		if ((check_special(SPECIAL_, str[i]) != -1 && i == 0 && str[i] != ';') \
			|| ((str[i] == '>' || str[i] == '<') && \
			i == (ft_strlen(str) - 1)))
			return (printf ("minishell: parse error near!\n"), 1);
		if (check_special(SPECIAL_, str[i]) != -1 && str[i + 1] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (check_special(SPECIAL_, str[i]) != -1)
				return (printf ("minishell: parse error near!\n"), 1);
		}
		else
			i++;
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_syntax3(char c, char check, int *count)
{
	if (check_special(SPECIAL_, c) != -1)
	{
		if (check != c)
			return (printf ("minishell: parse error near!\n"), 1);
		if (check == c)
		{
			(*count)++;
			if (*count == 2)
				return (printf ("minishell: parse error near!\n"), 1);
		}
	}
	if (check == '&' && *count == 0)
	{
		printf ("error: syntax!\n");
		return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_syntax2(char *str)
{
	int		i;
	int		cout;
	char	check;

	i = 0;
	cout = 0;
	while (str[i])
	{
		if (check_special(SPECIAL_, str[i]) != -1)
		{
			check = str[i++];
			if (check_syntax3(str[i], check, &cout))
				return (1);
		}
		else
		{
			cout = 0;
			i++;
		}
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

// void	print_data(t_info info)
// {
// 	while (info.head)
// 	{
// 		printf ("token:%d | cmd: %s | args: %s | in: %s | out: %s\n", \
// 			info.head->tokne, info.head->cmd, info.head->args, \
// 			info.head->in, info.head->out);
// 		info.head = info.head->next;
// 	}
// }

/* -------------------------------------------------------------------------- */

void free_info_cmds(t_cmds *cmds)
{
	if (cmds->cmd)
		free(cmds->cmd);
	if (cmds->args)
		free(cmds->args);
	if (cmds->in)
		free(cmds->in);
	if (cmds->out)
		free(cmds->out);
}

/* -------------------------------------------------------------------------- */

t_node	*new_node(t_cmds *cmds)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit (1);
	node->tokne = cmds->tokne;
	node->cmd = ft_strdup(cmds->cmd);
	node->args = ft_strdup(cmds->args);
	node->in = ft_strdup(cmds->in);
	node->out = ft_strdup(cmds->out);
	free_info_cmds(cmds);
	printf ("token:%d | cmd: %s | args: %s | in: %s | out: %s\n", \
			node->tokne, node->cmd, node->args, \
			node->in, node->out);
	return (node);
}

/* -------------------------------------------------------------------------- */

void	add_back(t_node **lst, t_node *node)
{
	t_node	*new;

	if (!node)
		return ;
	if (!lst[0])
	{
		lst[0] = node;
		node->next = node;
		return ;
	}
	new = lst[0];
	while (new->next != lst[0])
		new = new->next;
	node->next = NULL;
}

/* -------------------------------------------------------------------------- */

int	check_operator(t_info *info, int flag)
{
	if (flag == 0)
	{
		if (info->input[info->i] == PIPE || info->input[info->i] == OUT || \
			info->input[info->i] == IN || info->input[info->i] == SPACE )
			return (1);
	}
	if (flag == 1)
	{
		if (info->input[info->i] != PIPE && info->input[info->i] != OUT && \
			info->input[info->i] != IN && \
			info->input[info->i] != SPACE && info->input[info->i])
			return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

void	scape_space(t_info *info)
{
	while (info->input[info->i] && info->input[info->i] == SPACE)
		info->i++;
}

/* -------------------------------------------------------------------------- */

void	handel_args(t_info *info, t_cmds *cmds, char *str)
{
	int j;

	j = 0;
	scape_space(info);
	while (info->input[info->i] && \
		(info->input[info->i] == DOUBLEQ || info->input[info->i] == SINGELQ))
		info->i++;
	scape_space(info);
	while (info->input[info->i] && check_operator(info, 1) && \
		info->input[info->i] != DOUBLEQ && info->input[info->i] != SINGELQ)
		str[j++] = info->input[info->i++];
	scape_space(info);
	while (info->input[info->i] && \
		(info->input[info->i] == DOUBLEQ || info->input[info->i] == SINGELQ))
		info->i++;
	cmds->args = ft_strdup(str);
	ft_bzero(str, '\0');
}

/* -------------------------------------------------------------------------- */

void	handel_pipe(t_info *info, t_cmds *cmds)
{
	cmds->tokne = PIPE;
	cmds->cmd = NULL;
	cmds->in = NULL;
	cmds->out = NULL;
	cmds->args = NULL;
	add_back(&info->head, new_node(cmds));
	info->i++;
}

/* -------------------------------------------------------------------------- */

void	handel_in(t_info *info, t_cmds *cmds, char *str)
{
	int j = 0;
	info->i++;
	while (info->input[info->i] && check_operator(info, 1))
		str[j++] = info->input[info->i++];
	printf("|%s|\n", str);
	if (access(str, F_OK) != 0)
	{
		printf("no such file or directory!\n");
		exit(1);
	}
	if (access(str, R_OK | F_OK) == 0)
		cmds->in = ft_strdup(str);
	cmds->tokne = IN;
	cmds->cmd = NULL;
	cmds->out = NULL;
	cmds->args = NULL;
	ft_bzero(str, '\0');
	add_back(&info->head, new_node(cmds));
}

/* -------------------------------------------------------------------------- */

void	handel_command(t_info *info, t_cmds *cmds, char *str)
{
	int j;

	j = 0;
	scape_space(info);
	while (info->input[info->i] && check_operator(info, 1))
		str[j++] = info->input[info->i++];
	cmds->tokne = COMMAND;
	cmds->cmd = ft_strdup(str);
	cmds->in = NULL;
	cmds->out = NULL;
	ft_bzero(str, '\0');
	if (info->input[info->i] == SPACE)
		handel_args(info, cmds, str);
	else
		cmds->args = NULL;
	add_back(&info->head, new_node(cmds));
}

/* -------------------------------------------------------------------------- */

void	store_data(t_info *info)
{
	char	*str;
	t_cmds	*cmds;

	info->i = 0;
	info->head = NULL;
	str = (char *)malloc(sizeof(char) * 50);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!str || !cmds)
		exit(1);
	ft_bzero(str, '\0');
	while (info->input[info->i])
	{
		if (check_operator(info, 1))
		{
			handel_command(info, cmds, str);
			continue ;
		}
		else if (info->input[info->i] == PIPE)
		{
			handel_pipe(info, cmds);
			continue ;
		}
		else if (info->input[info->i] == IN)
		{
			handel_in(info, cmds, str);
			continue ;
		}
		// if (info->input[info->i] == OUT)
		// 	handel_out(info, str);
		// if (info->input[info->i] == HAREDOC)
		// 	handel_herdoc(info, str);
		// if (info->input[info->i] == APPEND)
		// 	handel_append(info, str);
		// if (info->input[info->i] == EXPAND)
		// 	handel_expand(info, str);
		info->i++;
	}
}

/* -------------------------------------------------------------------------- */

int	parcer(char *str, t_info *info)
{
	t_error	isexit;

	(void)info;
	isexit = check_syntax1(str);
	if (isexit == yes || !ft_strcmp(str, "\0"))
		return (free (str), 1);
	isexit = check_syntax2(str);
	if (isexit == yes || !ft_strcmp(str, "\0"))
		return (free (str), 1);
	store_data(info);
	return (0);
}

/* -------------------------------------------------------------------------- */
