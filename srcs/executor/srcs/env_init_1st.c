/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_1st.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

t_env_vars	*get_last_env_node(t_env_vars *head)
{
	t_env_vars	*node;

	if (head == NULL)
		return (NULL);
	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

/* -------------------------------------------------------------------------- */

void	add_node_to_env(t_env_vars *node, t_env_vars **head)
{
	t_env_vars	*tracer;

	tracer = get_last_env_node(*head);
	if (tracer == NULL)
		*head = node;
	else
		tracer->next = node;
}

/* -------------------------------------------------------------------------- */

void	free_env(t_env_vars *head)
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

int	add_key_only(char *input, t_env_vars **head)
{
	t_env_vars	*node;

	node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if (node == NULL)
		return (-1);
	node->key = ft_strdup(input);
	if (node->key == NULL)
		return (free(node), -1);
	add_node_to_env(node, head);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	overwrite_key_value(char *input, t_env_vars **head, char *sep)
{
	char		*key;
	char		*value;
	t_env_vars	*node;

	key = ft_substr(input, 0, (sep - input) / sizeof(char));
	if (key == NULL)
		return (-1);
	node = get_env_var(key, *head);
	value = ft_strdup(sep + 1);
	if (value == NULL)
		return (free(key), -1);	
	free(node->value);
	node->value = value;
	return (0);
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
	char	*output;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err("Failed to get PWD"), NULL);
	return (ft_strjoin("PATH=", cwd));
}

/* -------------------------------------------------------------------------- */

char	*get_cwd_env_var(void)
{
	char 	cwd[PATH_MAX];
	char	*output;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err("Failed to get PWD"), NULL);
	return (ft_strjoin("PATH=", cwd));
}

/* -------------------------------------------------------------------------- */

int	set_default_pwd(t_env_vars **head)
{
	char	*env_var;

	env_var = get_cwd_env_var();
	if (env_var == NULL)
		return (-1);
	if (init_node(env_var, head) != 0)
		return (free(env_var), -1);
	return (free(env_var), 0);
}

/* -------------------------------------------------------------------------- */

int	set_shell_lvl(t_env_vars **head)
{
	t_env_vars	*node;
	int			shlvl_int;
	char		*shlvl_str;
	char		*shlvl_env;

	node = get_env_var("SHLVL");
	if (node == NULL)
		return (init_node("SHLVL=1", head));
	shlvl_int = ft_atoi(node->value);
	shlvl_str = ft_itoa(++shlvl_int);
	shlvl_env = ft_strjoin("SHLVL=", shlvl_str);
	if (shlvl_env == NULL)
		return (-1);
	return (init_node(shlvl_env, head));
}

/* -------------------------------------------------------------------------- */

int	set_default_pwd(t_env_vars **head)
{
	char	*env_var;

	env_var = get_cwd_env_var();
	if (env_var == NULL)
		return (-1);
	if (init_node(env_var, head) != 0)
		return (free(env_var), -1);
	return (free(env_var), 0);
}

/* -------------------------------------------------------------------------- */
// Shell level
// OLDPWD
// PWD with no path, or no PWD at all (use macro <paths.h>)
// '+=' with empty value: do nothing
int	set_default_env_vars(t_env_vars **head)
{
	set_default_pwd(head);
	set_shell_lvl(head);
	init_node("OLDPWD", head);

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
		if (init_node(envp[i++], &head) != 0)
			return (NULL);
	}
	return (head);
}

/* -------------------------------------------------------------------------- */
