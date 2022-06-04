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
			|| ((str[i] == '>' || str[i]	== '<') && \
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

// void free_info_cmds(t_info *info)
// {
// 	if (info->cmds->cmd)
// 		free(info->cmds->cmd);
// 	if (info->cmds->args)
// 		free(info->cmds->args);
// 	if (info->cmds->in)
// 		free(info->cmds->in);
// 	if (info->cmds->out)
// 		free(info->cmds->out);
// }

// t_node	*new_node(t_info *info)
// {
// 	t_node	*node;

// 	node = (t_node *)malloc(sizeof(t_node));
// 	if (!node)
// 		exit (1);
// 	node->tokne = info->cmds->tokne;
// 	node->cmd = ft_strdup(info->cmds->cmd);
// 	node->args = ft_strdup(info->cmds->args);
// 	node->in = ft_strdup(info->cmds->in);
// 	node->out = ft_strdup(info->cmds->out);
// 	free_info_cmds(info);
// 	return (node);
// }

// void	add_back(t_node **lst, t_node *node)
// {
// 	t_node	*new;

// 	if (!node)
// 		return ;
// 	if (!lst[0])
// 	{
// 		lst[0] = node;
// 		node->next = node;
// 		return ;
// 	}
// 	new = lst[0];
// 	while (new->next != lst[0])
// 		new = new->next;
// 	new->next = node;
// 	node->next = NULL;
// }

// int	check_operator(t_info *info, int i, int flag)
// {
// 	if (flag == 0)
// 	{
// 		if (info->input[i] == PIPE || info->input[i] == OUT || \
// 			info->input[i] == IN || \
// 			info->input[i] == SEMICOLON || info->input[i] == SPACE)
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	else if (flag == 1)
// 	{
// 		if (info->input[i] != PIPE || info->input[i] != OUT || \
// 			info->input[i] != IN || \
// 			info->input[i] != SEMICOLON || info->input[i] != SPACE)
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	return (0);
// }

// void	handel_args(t_info *info, char *str, int *j)
// {
// 	while (info->input[info->i] == ' ')
// 		info->i++;
// 	while (info->input[info->i] == DOUBLEQ || \
// 		info->input[info->i] == SINGELQ)
// 		info->i++;
// 	while (check_operator(info, info->i, 1))
// 	{
// 		str[*j] = info->input[info->i];
// 		(*j)++;
// 		info->i++;
// 	}
// 	info->cmds->args = ft_strdup(str);
// 	*j = 0;
// 	ft_bzero(str, 0);

// }

// void	store_data(t_info *info)
// {
// 	int		j;
// 	char	*str;

// 	j = 0;
// 	info->i = 0;
// 	str = (char *)malloc(sizeof(char) * 50);
// 	if (!str)
// 		exit(1);
// 	ft_bzero(str, 0);
// 	while (info->input[info->i])
// 	{
// 		if (check_operator(info, info->i, 0))
// 		{
// 			info->cmds->tokne = COMMAND;
// 			info->cmds->cmd = ft_strdup(str);
// 			info->cmds->in = NULL;
// 			info->cmds->out = NULL;
// 			ft_bzero(str, 0);
// 			j = 0;
// 			if (info->input[info->i] == ' ')
// 				handel_args(info, str, &j);
// 			else
// 				info->cmds->args = NULL;
// 			add_back(&info->head, new_node(info));
// 		}
// 		if (info->input[info->i] == PIPE)
// 			handel_pipe(info, str);
// 		if (info->input[info->i] == SEMICOLON)
// 			handel_semicolon(info, str);
// 		if (info->input[info->i] == IN)
// 			handel_in(info, str);
// 		if (info->input[info->i] == OUT)
// 			handel_out(info, str);
// 		if (info->input[info->i] == HAREDOC)
// 			handel_herdoc(info, str);
// 		if (info->input[info->i] == APPEND)
// 			handel_append(info, str);
// 		if (info->input[info->i] == EXPAND)
// 			handel_expand(info, str);
// 		str[j] = info->input[info->i];
// 		j++;
// 		info->i++;
// 	}
// }

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
	// store_data(info);
	return (0);
}

/* -------------------------------------------------------------------------- */
