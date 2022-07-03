/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:30:02 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/07/03 02:16:21 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* -------------------------------------------------------------------------- */

char	*get_env(const char *var, t_env_vars *env_head)
{
	t_env_vars	*node;

	node = env_head;
	while (node)
	{
		if (ft_strcmp(node->key, var) == 0)
			return (node->value);
		node = node->next; 
	}
	return (NULL);
}

/* -------------------------------------------------------------------------- */

void	free_info(t_info *info)
{
	t_node	*tmp;
	t_node	*ptr;

	tmp = info->head;
	free(info->input);
	free(info->input1);
	while (tmp != NULL)
	{
		free(tmp->data);
		free(tmp->path);
		if (tmp->cmd_split)
			free_split(tmp->cmd_split);
		ptr = tmp;
		tmp = tmp->next;
		free(ptr);
	}
	info->head = NULL;
	info->cmds = NULL;
}

/* -------------------------------------------------------------------------- */

static int	prompt(t_info *info, char **envp)
{
	char		*rdln_output;
	t_env_vars	*env_head;

	g_glob.exit = 0;
	env_head = conv_env(envp);
	g_glob.env_head = &env_head;
	handle_signals();
	while (1)
	{
		handle_signals();
		rdln_output = readline(RL_SUCCESS);
		if (rdln_output == NULL)
		{
			printf("exit\n");
			restore_ctrl();
			return (g_glob.exit);
		}
		info->input = ft_strtrim(rdln_output, WHITESPACE);
		if (*(info->input) == '\0')
			continue ;
		add_history(rdln_output);
		free(rdln_output);
		if (lexer_start(info) || parcer(info))
		{
			free(info->input);
			continue ;
		}
		handle_execution(info, &env_head);
		free_info(info);
	}
	return (0);
}
// We have a problem with the readline library.

/* -------------------------------------------------------------------------- */

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	hide_ctrl();
	if (ft_strcmp(av[0], "./minishell") == 0 && ac == 1)
		if (prompt(&info, envp) == 1)
			return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */
