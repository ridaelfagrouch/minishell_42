/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_misc_2.c                                      :+:      :+:    :+:   */
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

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i++] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	free_linked_list(t_node *head)
{
	t_node	*node;
	t_node	*next;

	node = head;
	while (node)
	{
		next = node->next;
		free(node->data);
		close(node->file_fd);
		free(node->path);
		free_double_pointer(node->cmd_split);
		free(node);
		node = next;
	}
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	count_command_nodes(t_node *head)
{
	t_node	*tracer;
	int		count;

	count = 0;
	tracer = head;
	while (tracer)
	{
		if (tracer->token == COMMAND)
			count++;
		tracer = tracer->next;
	}
	return (count);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	unlink_heredoc_files(t_node *head)
{
	t_node	*node;

	node = head;
	while (node)
	{
		if (node->token == IN && node->cmd_flag == 69)
			unlink(node->data);
		node = node->next;
	}
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	close_fds(t_node *head)
{
	t_node	*tracer;

	tracer = head;
	while (tracer)
	{
		if (tracer->token == IN || tracer->token == OUT || \
			tracer->token == APPEND)
			close(tracer->file_fd);
		tracer = tracer->next;
	}
}
