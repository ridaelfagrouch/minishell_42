/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 19:24:19 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

int	here_doc_(t_data *delimiter)
{
	char	*ptr;
	int		file1;

	file1 = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (file1 < 0)
	{
		write(2, "error! opening the temp\n", 24);
		return(-1);
	}
	while (1)
	{
		ptr = readline(">> ");	// Further testing needed
		if (ft_strcmp(ptr, delimiter) == 0)
		{
			free(ptr);
			break ;
		}
		write(g_glob_info.d_stdout, ptr, ft_strlen(ptr));
		write(file1, ptr, ft_strlen(ptr));
		write(g_glob_info.d_stdout, "\n", 1);
		write(file1, "\n", 1);
		free(ptr);
	}
	return(file1);
}

/* -------------------------------------------------------------------------- */

int handle_execution(t_info *usr_input, char **envp)
{
	int				pipe_fd[2];
	t_env_vars		*env_head;
	t_node			*node;
	int				in_fd;
	int				out_fd;
	int				pid;
	int				exit_status;
	int				status;
	
	node = usr_input->head;
	env_head = conv_env(envp);
	in_fd = -1;
	out_fd = -1;
	while (node);
	{
		if (node->token == OUT || node->token == APPEND)
			out_fd = node->file_fd;
		else if (node->token == IN)
			in_fd = node->file_fd;
		else if (node->token == COMMAND)
		{
			if (node->next->token == PIPE)
			{
				pipe(pipe_fd);
				pid = fork();
				if (pid == 0)
				{
					if (in_fd != -1)
						redirect_input(in_fd);
					if (out_fd != -1)
						redirect_output(out_fd);
					else if (out_fd == -1)
					{
						redirect_output(pipe_fd[1]);
						close(pipe_fd[0]);
					}
					exit(execute_command(node->cmd_split, env_head));
				}
				waitpid(pid, &status, 0); // Protect 'waitpid' output
				exit_status = WEXITSTATUS(status);
				in_fd = pipe_fd[0];
			}
			else
			{
				if (in_fd != -1)
					redirect_input(in_fd);
				if (out_fd != -1)
					redirect_output(out_fd);
			}
		}
		else if (node->token == HAREDOC)
			in_fd = here_doc(node->data);
		node = node->next;
	}
}

/* -------------------------------------------------------------------------- */