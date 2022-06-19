/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 21:37:48 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
	Built-In vs Shell Programs

	Built-in commands are executed as a function.But it may fork first if you 
	use it in a pipeline '|', for example:
		$ cd / | echo 
	it forks and calls cd in the child. You can also notice this by how 
	the directory doesn't actually change.
*/

/* -------------------------------------------------------------------------- */

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
			return (NULL);			// should free allocated mem
		ptr = new_envp[i];
		new_envp[i] = ft_strjoin(ptr, node->value);
		free(ptr);
		if (new_envp[i] == NULL)
			return (NULL);			// should free allocated mem
		node = node->next;
		++i;
	}
	return (new_envp);
}

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

static int	execute_non_builtin(char **input, t_env_vars *head)
{
	char	**env_arr;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		env_arr = lnkd_lst_env_to_char(head);
		if (execve(input[0], input, env_arr) != 0)
			exit(-1);
		//free(env_arr);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

/* -------------------------------------------------------------------------- */

int	execute_command(char **input, t_env_vars *env_vars)
{
	if (input == NULL || input[0] == NULL)
		return (-1);
	else if (ft_strcmp(input[0], "echo") == 0)
		return (echo_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "cd") == 0)
		return (cd_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "pwd") == 0)
		return (pwd_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "export") == 0)
		return (export_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "unset") == 0)
		return (unset_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "env") == 0)
		return (env_cmd(input, env_vars));
	else if (ft_strcmp(input[0], "exit") == 0)
		return(exit_cmd(input, env_vars), 0);
	return (execute_non_builtin(input, env_vars));
	//return (0);
}

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
