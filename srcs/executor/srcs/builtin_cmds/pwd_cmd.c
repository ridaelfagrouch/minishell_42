/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

int	pwd_cmd(char **input, t_env_vars **env_head)
{
	t_env_vars	*node;
	char		cwd[PATH_MAX];

	input = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		node = get_env_var("PWD", *env_head);
		if (node)
		{
			free(node->value);
			node->value = ft_strdup(cwd);
		}
		printf("%s\n", cwd);
		return (0);
	}
	node = get_env_var("PWD", *env_head);
	if (node == NULL)
		return (1);
	printf("%s\n", node->value);
	return (0);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	Print the absolute pathname of the current working directory. The return
	status is zero unless an error is encountered while determining the name
	of the current directory or an invalid option is supplied.
*/

/* -------------------------------------------------------------------------- */
