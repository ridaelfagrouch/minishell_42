/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 19:20:39 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	heredoc_filler(int heredoc, char *delimiter)
{
	char	*ptr;

	while (1)
	{
		ptr = readline("> ");
		if (!ptr || !ft_strcmp(ptr, delimiter))
			break ;
		ptr = input_expand(put_expand(ptr));
		write(heredoc, ptr, ft_strlen(ptr));
		write(heredoc, "\n", 1);
		free(ptr);
		ptr = NULL;
	}
	free(ptr);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	heredoc_handler(char *delimiter, char *filename)
{
	struct sigaction	n_act;
	pid_t				pid;
	int					child_status;
	int					heredoc;

	pid = fork();
	if (pid == 0)
	{
		n_act.sa_handler = SIG_DFL;
		sigaction(SIGINT, &n_act, NULL);
		heredoc = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (heredoc < 0)
		{
			print_err(NULL, "heredoc", "internal error detected");
			exit(1);
		}
		heredoc_filler(heredoc, delimiter);
		close(heredoc);
		exit(0);
	}
	waitpid(pid, &child_status, 0);
	return (WEXITSTATUS(child_status));
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

t_node	*get_first_heredoc_node(t_node *head)
{
	t_node	*tracer;

	tracer = head;
	while (tracer && tracer->token != HEREDOC)
		tracer = tracer->next;
	return (tracer);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

int	count_heredocs(t_node *head)
{
	t_node	*node;
	int		count;

	count = 0;
	node = head;
	while (node)
	{
		if (node->token == HEREDOC)
			count++;
		node = node->next;
	}
	return (count);
}

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

char	**name_heredoc_files(int count)
{
	char	**file_names;
	char	*file_name;
	int		i;

	file_names = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!file_names)
		return (NULL);
	i = 0;
	while (i < count)
	{
		file_name = ft_itoa(i);
		file_names[i++] = ft_strjoin(HEREDOC_PATH, file_name);
		free(file_name);
		file_name = NULL;
	}
	return (file_names);
}
