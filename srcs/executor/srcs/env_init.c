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

/* -------------------------------------------------------------------------- */

/*
** int	set_default_pwd(t_env_vars **head)
** {
** 	char	*env_var;
** 
** 	env_var = get_cwd_env_var();
** 	if (env_var == NULL)
** 		return (-1);
** 	if (init_node(env_var, head) != 0)
** 		return (free(env_var), -1);
** 	return (free(env_var), 0);
** }
*/

/* -------------------------------------------------------------------------- */

/*
** int	set_shell_lvl(t_env_vars **head)
** {
** 	t_env_vars	*node;
** 	int			shlvl_int;
** 	char		*shlvl_str;
** 	char		*shlvl_env;
** 
** 	node = get_env_var("SHLVL", *head);
** 	if (node == NULL)
** 		return (init_node("SHLVL=1", head));
** 	shlvl_int = ft_atoi(node->value);
** 	shlvl_str = ft_itoa(++shlvl_int);
** 	shlvl_env = ft_strjoin("SHLVL=", shlvl_str);
** 	if (shlvl_env == NULL)
** 		return (-1);
** 	return (init_node(shlvl_env, head));
** }
*/

/* -------------------------------------------------------------------------- */

/*
** int	set_default_env_vars(t_env_vars **head)
** {
** 	if (set_default_pwd(head) \
** 		|| set_shell_lvl(head) \
** 		|| init_node("OLDPWD", head) \
** 		|| set_launch_prog(head, ))
** 		return (0);
** }
*/

/* -------------------------------------------------------------------------- */

static void	free_env_linked_list(t_env_vars *head)
{
	t_env_vars	*node;
	t_env_vars	*tracer;

	node = head;
	while (node)
	{
		tracer = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = tracer;
	}
}

/* -------------------------------------------------------------------------- */

static int	append_node(t_env_vars **head, char *key, char *value)
{
	t_env_vars	**tracer;

	tracer = head;
	while (*tracer)
		tracer = &(*tracer)->next;
	(*tracer) = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if ((*tracer) == NULL)
		return (print_err("malloc", NULL, "allocation failure"), \
			free_env_linked_list(*head), -1);
	(*tracer)->key = key;
	(*tracer)->value = value;
	return (0);
}

/* -------------------------------------------------------------------------- */

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
		printf("\nHello there\n");
		free(ptr);
	}
	return (key_value);
}

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

int	process_env_var(t_env_vars **head, char *env_var)
{
	char		**key_value;
	t_env_vars	*node;

	key_value = parse_env_var(*head, env_var);
	node = get_env_var(key_value[0], *head);
	if (node == NULL)
		return (append_node(head, key_value[0], key_value[1]));
	free(node->key);
	free(node->value);
	node->key = key_value[0];
	node->value = key_value[1];
	return (0);
}

/* -------------------------------------------------------------------------- */


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
	//return (set_default_env(head), head);
	return (head);
}

/* -------------------------------------------------------------------------- */
