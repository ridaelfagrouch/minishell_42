/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 19:20:39 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* --------------------------- NON BUILT IN --------------------------------- */

static char	**init_new_envp(t_env_vars *head, char **new_envp)
{
	t_env_vars	*node;
	void		*ptr;
	int			i;

	i = 0;
	node = head;
	while (node)
	{
		new_envp[i] = ft_strjoin(node->key, "=");
		if (new_envp[i] == NULL)
			return (free_double_pointer(new_envp), NULL);
		ptr = new_envp[i];
		new_envp[i] = ft_strjoin(ptr, node->value);
		free(ptr);
		if (new_envp[i] == NULL)
			return (free_double_pointer(new_envp), NULL);
		node = node->next;
		++i;
	}
	return (new_envp);
}

/* --------------------------- NON BUILT IN --------------------------------- */

static char	**lnkd_lst_env_to_char(t_env_vars *head)
{
	t_env_vars	*tracer;
	char		**output;
	int			count;

	tracer = head;
	count = 0;
	while (tracer)
	{
		tracer = tracer->next;
		++count;
	}
	output = (char **)ft_calloc(count + 1, sizeof(char *));
	if (output == NULL)
		return (NULL);
	output = init_new_envp(head, output);
	return (output);
}

/* --------------------------- NON BUILT IN --------------------------------- */

static int	execute_non_builtin(char *cmd, char **input, t_env_vars *head)
{
	char	**env_arr;

	env_arr = lnkd_lst_env_to_char(head);
	if (execve(cmd, input, env_arr) != 0)
		return (-1);
	return (0);
}

/* ----------------------------- BUILT IN ----------------------------------- *\
TODO	Adjust the exit status of the Shell Built-Ins
\* -------------------------------------------------------------------------- */
int	execute_builtins(char **input, t_env_vars **env_vars)
{
	if (ft_strcmp_tl(input[0], "echo") == 0)
		return (echo_cmd(input, env_vars));
	else if (ft_strcmp_tl(input[0], "cd") == 0)
		return (cd_cmd(input, env_vars));
	else if (ft_strcmp_tl(input[0], "pwd") == 0)
		return (pwd_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "export") == 0)
		return (export_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "unset") == 0)
		return (unset_cmd(input, env_vars));
	else if (ft_strcmp_tl(input[0], "env") == 0)
		return (env_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "exit") == 0)
		return (exit_cmd(input, env_vars), 0);
	return (-1);
}

/* --------------------------------- MAIN ----------------------------------- */

int	execute_command(t_node *node, t_env_vars **env_vars)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strstr_tl(BUILT_INS, node->cmd_split[0]))
			exit(execute_builtins(node->cmd_split, env_vars));
		exit(execute_non_builtin(node->path, node->cmd_split, *env_vars));
	}
	ignore_signal();
	if (!node->next)
	{
		waitpid(pid, &status, 0);
	}
	handle_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

// * ---------------------------------------------------------------------- * ///
