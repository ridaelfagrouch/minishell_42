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
	t_quote			*quotes;
	int				dq;

	quotes = NULL;
	dq = -1;
	i = 0;
	while (str[i])
	{
		if ((check_special(SPECIAL_, str[i]) != -1 && i == 0 && str[i] != ';') \
			|| ((str[i] == '>' || str[i] == '<') && \
			i == (ft_strlen(str) - 1)))
			return (printf ("minishell: parse error near 1!\n"), 1);
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(&quotes, str, i, &dq);
		if (check_special(SPECIAL_, str[i]) != -1 && str[i + 1] == ' ' && \
			quoted(quotes, 0) == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (check_special(SPECIAL_, str[i]) != -1)
				return (printf ("minishell: parse error near 2!\n"), 1);
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
			return (printf ("minishell: parse error near 3 !\n"), 1);
		if (check == c)
		{
			(*count)++;
			if (*count == 2)
				return (printf ("minishell: parse error near! 4\n"), 1);
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
	int				i;
	int				cout;
	char			check;
	t_quote			*quotes;
	int				dq;

	quotes = NULL;
	dq = -1;
	i = 0;
	cout = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(&quotes, str, i, &dq);
		if (check_special(SPECIAL_, str[i]) != -1 && quoted(quotes, 0) != 0)
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

t_node	*new_node(t_cmds *cmds)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit (1);
	node->token = cmds->token;
	node->data = ft_strdup(cmds->data);
	if (cmds->data)
		free(cmds->data);
	printf ("token:%d | data: %s\n", node->token, node->data);
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

void	scape_space(t_info *info)
{
	while (info->input[info->i] && info->input[info->i] == ' ')
		info->i++;
}

/* -------------------------------------------------------------------------- */

void	handel_pipe(t_info *info, t_cmds *cmds)
{
	cmds->token = PIPE;
	cmds->data = NULL;
	add_back(&info->head, new_node(cmds));
}

 /* -------------------------------------------------------------------------- */

void	while_operator(t_info *info, char *str)
{
	int	j;

	j = 0;
	while (info->input[info->i] && check_operator(info, 1))
	{
		while (info->input[info->i] == DOUBLEQ || \
			info->input[info->i] == SINGELQ)
			info->i++;
		str[j] = info->input[info->i];
		info->i++;
		j++;
	}
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
		cmds->data = ft_strdup(str);
	else
		cmds->data = NULL;
	if (i == 1)
		cmds->token = APPEND;
	else
		cmds->token = OUT;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
}

/* -------------------------------------------------------------------------- */

void	handel_command(t_info *info, t_cmds *cmds, char *str)
{
	int	j;

	j = 0;
	scape_space(info);
	while_operator(info, str);
	cmds->token = COMMAND;
	cmds->data = ft_strdup(str);
	ft_bzero(str, 50);
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 50);
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
	ft_bzero(str, 50);
	while (info->input[info->i])
	{
		if (check_operator(info, 1) && info->input[info->i] != ' ')
		{
			handel_command(info, cmds, str);
			continue ;
		}
		else if (info->input[info->i] == IN)
		{
			handel_in(info, cmds, str);
			continue ;
		}
		else if (info->input[info->i] == OUT || info->input[info->i] == APPEND)
		{
			handel_out(info, cmds, str);
			continue ;
		}
		else if (info->input[info->i] == HAREDOC)
		{
			handel_herdoc(info, cmds, str);
			continue ;
		}
		else if (info->input[info->i] == PIPE)
			handel_pipe(info, cmds);
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
