/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

/* -------------------------------------------------------------------------- */

void	unset_error(char *varname, char *message)
{
	write(2, varname, ft_strlen(varname));
	write(2, ":\t", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

/* -------------------------------------------------------------------------- */

void	delete_node(t_env_vars *node, t_env_vars *env_head)
{
	t_env_vars	*tracer;

	tracer = env_head;
	while (tracer && tracer->next != node)
		tracer = tracer->next;
	tracer->next = tracer->next->next;
	free(node->key);
	free(node->value);
	free(node);
}

/* -------------------------------------------------------------------------- */

int	unset_cmd(char **input, t_env_vars *env_head)
{
	t_env_vars	*node;
	int			i;

	i = 0;
	while (input[++i])
	{
		node = get_env_var(input[i], env_head);
		if (node == NULL)
			unset_error(input[i], "not a valid identifier");
		else
			delete_node(node, env_head);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

/*
	CMD RULES:

	If no options are supplied, each name refers to a variable; if there is
	no variable by that name, a function with that name, if any, is unset.
	Readonly variables and functions may not be unset. Some shell variables
	lose their special behavior if they are unset; such behavior is noted in
	the description of the individual variables. The return status is zero
	unless a name is readonly.
*/

/* -------------------------------------------------------------------------- */
//cttDwlbrO3S@Temp13+