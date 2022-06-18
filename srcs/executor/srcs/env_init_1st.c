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
