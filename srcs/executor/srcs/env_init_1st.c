/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
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

static int	append_node(t_env_vars **head, char **key_value)
{
	t_env_vars	**tracer;

	tracer = head;
	while ((*tracer))
		tracer = &(*tracer)->next;
	(*tracer) = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if ((*tracer) == NULL)
		return (print_err("malloc", NULL, "allocation failure"), \
			free_env_linked_list(*head), -1);
	(*tracer)->key = key_value[0];
	(*tracer)->value = key_value[1];
	(*tracer)->next = NULL;
	free(key_value);
	return (0);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

static char	**parse_value(char **key_value, char *env_var, t_env_vars *head)
{
	char		*sep;
	t_env_vars	*node;
	void		*ptr;

	sep = ft_strstr(env_var, "+=");
	key_value[0] = ft_substr(env_var, 0, (sep - env_var) / sizeof(char));
	key_value[1] = ft_strdup(sep + (2 * sizeof(char)));
	node = get_env_var(key_value[0], head);
	if (node != NULL)
	{
		ptr = key_value[1];
		key_value[1] = ft_strjoin(node->value, ptr);
		free(ptr);
	}
	return (key_value);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

static char	**parse_env_var(t_env_vars *head, char *env_var)
{
	char		*sep;
	char		**key_value;

	key_value = (char **)ft_calloc(2, sizeof(char *));
	if (key_value == NULL)
		return (print_err("malloc", NULL, "allocation failure"), NULL);
	if (ft_strstr(env_var, "+="))
		key_value = parse_value(key_value, env_var, head);
	else if (ft_strchr(env_var, '='))
	{
		sep = ft_strchr(env_var, '=');
		key_value[0] = ft_substr(env_var, 0, (sep - env_var) / sizeof(char));
		key_value[1] = ft_strdup(sep + (1 * sizeof(char)));
	}
	else
	{
		key_value[0] = ft_strdup(env_var);
		key_value[1] = NULL;
	}
	return (key_value);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	process_env_var(t_env_vars **head, char *env_var)
{
	char		**key_value;
	t_env_vars	*node;

	key_value = parse_env_var(*head, env_var);
	node = get_env_var(key_value[0], *head);
	if (node == NULL)
		return (append_node(head, key_value));
	free(node->key);
	free(node->value);
	node->key = key_value[0];
	node->value = key_value[1];
	free(key_value);
	return (0);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

t_env_vars	*conv_env(char **envp)
{
	int			i;
	t_env_vars	*head;

	i = 0;
	head = NULL;
	while (envp && envp[i])
	{
		if (process_env_var(&head, envp[i++]))
			return (free_env_linked_list(head), NULL);
	}
	if (set_default_pwd(&head) || set_shell_lvl(&head))
		print_err("env", "an error occured while setting env variables", NULL);
	return (head);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */
