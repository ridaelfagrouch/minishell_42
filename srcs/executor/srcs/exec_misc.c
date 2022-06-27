/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

t_env_vars	*get_env_var(char *varname, t_env_vars *env_head)
{
	t_env_vars	*node;

	node = env_head;
	while (node && ft_strcmp(node->key, varname))
		node = node->next;
	return (node);
}

/* -------------------------------------------------------------------------- */

// char	*get_env_var(char *varname, t_env_vars *env_head)
// {
// 	char	*output;

// 	node = env_head;
// 	while (node && ft_strcmp(node->key, varname))
// 		node = node->next;
// 	return (node);
// }

/* -------------------------------------------------------------------------- */

char	**split_path_env_var(t_env_vars *env_head)
{
	t_env_vars	*paths;
	char		**splited_paths;

	paths = get_env_var("PATH", env_head);
	if (paths->value == NULL)
		return (NULL);
	splited_paths = ft_split(paths->value, ':');
	return (splited_paths);
}

/* -------------------------------------------------------------------------- */

void	free_two_dim_arr(char **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i++])
		free(sorted_env[i++]);
	free(sorted_env);
}

/* -------------------------------------------------------------------------- */

char	**copy_envp(char **envp)
{
	int	count;
	char **output;
	int	i;

	count= 0;
	while (envp[count])
		count++;
	output = (char **)ft_calloc(count + 1, sizeof(char *));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		output[i] = ft_strdup(envp[i]);
		if (output[i++] == NULL)
			return (free_two_dim_arr(output), NULL);
	}
	return (output);
}

/* -------------------------------------------------------------------------- */

void	print_err(char *cmd, char *input, char *msg)
{
	write(STDERR_FILENO, "minishell: ", 11 * sizeof(char));
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2 * sizeof(char));
	}
	if (input)
	{
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, ": ", 2 * sizeof(char));
	}
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1 * sizeof(char));
	}
}

/* -------------------------------------------------------------------------- */



/* -------------------------------------------------------------------------- */

char	*get_wildcard_data(void) // should be (char *str)
{
	DIR				*dirp;
	struct dirent	*dp;
	void			*ptr;
	char			*output;

	dirp = opendir(".");
	if (dirp == NULL)
		return (NULL);
	output = ft_strdup("");
	if (output == NULL)
		return ((void)closedir(dirp), NULL);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (ft_strcmp(".", dp->d_name) && ft_strcmp(".." , dp->d_name))
		{
			ptr = output;
			output = ft_strjoin(ptr, " ");
			free(ptr);
			if (output == NULL)
				return ((void)closedir(dirp), NULL);
			ptr = output;
			output = ft_strjoin(ptr, dp->d_name);
			free(ptr);
			if (output == NULL)
				return ((void)closedir(dirp), NULL);
		}
		dp = readdir(dirp);
	}
	(void)closedir(dirp);
	return (output);
}

/* -------------------------------------------------------------------------- */
