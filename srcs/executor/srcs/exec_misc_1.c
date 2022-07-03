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

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

t_env_vars	*get_env_var(char *varname, t_env_vars *env_head)
{
	t_env_vars	*node;

	node = env_head;
	while (node && ft_strcmp(node->key, varname))
		node = node->next;
	return (node);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	free_two_dim_arr(char **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i++])
		free(sorted_env[i++]);
	free(sorted_env);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

char	*put_expand(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			ptr[i] = EXPAND;
		i++;
	}
	return (ptr);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	is_mult_pipes(t_node *node)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = node;
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
