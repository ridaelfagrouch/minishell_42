/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_nd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

void	print_err(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

/* -------------------------------------------------------------------------- */

int	add_key_value(char *input, t_env_vars **head, char *sep)
{
	char		*key;
	char		*value;
	t_env_vars	*node;

	key = ft_substr(input, 0, (sep - input) / sizeof(char));
	if (key == NULL)
		return (-1);
	value = ft_strdup(sep + 1);
	if (get_env_var(key, *head))
		return (free(key), overwrite_key_value(input, head, sep));
	if (value == NULL)
		return (free(key), -1);
	node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if (node == NULL)
		return (free(key), free(value), -1);
	node->key = key;
	node->value = value;
	add_node_to_env(node, head);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	append_value(char *input, t_env_vars **head, char *sep)
{
	char		*key;
	char		*value;
	t_env_vars	*node;
	void		*ptr;

	key = ft_substr(input, 0, (sep - input) / sizeof(char));
	if (key == NULL)
		return (-1);
	node = get_env_var(key, *head);
	if (node == NULL)
		return (free(key), add_key_value(input, head, sep));
	value = ft_strdup(sep + 1);
	if (value == NULL)
		return (free(key), -1);
	ptr = node->value;
	node->value = ft_strjoin(node->value, value);
	if (node->value == NULL)
	{
		node->value = ptr;
		return (free(key), free(value), -1);
	}
	return (free(ptr), 0);
}

/* -------------------------------------------------------------------------- */

int	init_node(char *input, t_env_vars **head)
{
	char		*sep;

	if (input == NULL || *input == '\0')
		return (-1);
	sep = ft_strchr(input, '=');
	if (sep == input)
		return (-1); // Print error
	if (sep == NULL)
		return (add_key_only(input, head));
	else if (sep && *(sep - 1) == '+' && *(sep + 1))
		return (append_value(input, head, sep));
	else if (sep != NULL)
		return (add_key_value(input, head, sep));
	return (print_err("Not a valid Env Variable"), -1);
}

/* -------------------------------------------------------------------------- */

char	*get_cwd_env_var(void)
{
	char 	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err("Failed to get PWD"), NULL);
	return (ft_strjoin("PATH=", cwd));
}

/* -------------------------------------------------------------------------- */
