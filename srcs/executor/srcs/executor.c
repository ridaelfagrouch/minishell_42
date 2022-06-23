/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/23 17:40:03 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

void	here_doc_(char *delimiter)
{
	char	*ptr;
	int		file1;

	file1 = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (file1 < 0)
	{
		write(2, "error! opening the tmp\n", 24);
		return ;
	}
	while (1)
	{
		ptr = readline(">> ");	// Further testing needed
		if (ft_strcmp(ptr, delimiter) == 0)
		{
			free(ptr);
			break ;
		}
		write(file1, ptr, ft_strlen(ptr));
		write(file1, "\n", 1);
		free(ptr);
	}
	close(file1);
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
	
	store_stds();
	node = usr_input->head;
	env_head = conv_env(envp);
	in_fd = -1;
	out_fd = -1;
	while (node)
	{
		if (node->token == OUT || node->token == APPEND)
			out_fd = node->file_fd;
		else if (node->token == IN)
			in_fd = node->file_fd;
		else if (node->token == COMMAND)
		{
			if (node->next && node->next->token == PIPE)
			{
				pipe(pipe_fd);
				pid = fork();
				if (pid == 0)
				{
					if (in_fd != -1)
						redirect_input(in_fd);
					if (out_fd != -1)
					{
						redirect_output(out_fd);
						out_fd = -1;
					}
					else if (out_fd == -1)
						redirect_output(pipe_fd[1]);
					exit(execute_command(node, env_head));
				}
				waitpid(pid, &status, 0);
				close(pipe_fd[1]);
				g_glob.exit_status = WEXITSTATUS(status);
				in_fd = pipe_fd[0];
			}
			else
			{
				if (ft_strstr_tl(BUILT_INS, node->cmd_split[0]))
				{
					if (in_fd != -1)
						redirect_input(in_fd);
					if (out_fd != -1)
					{
						redirect_output(out_fd);
						out_fd = -1;
					}
					g_glob.exit_status = execute_command(node, env_head);
					dup2(g_glob.d_stdout, STDOUT_FILENO);
				}
				else
				{
					pid = fork();
					if (pid == 0)
					{
						if (in_fd != -1)
							redirect_input(in_fd);
						if (out_fd != -1)
						{
							redirect_output(out_fd);
							out_fd = -1;
						}
						else
							dup2(g_glob.d_stdout, STDOUT_FILENO);
						exit_status = execute_command(node, env_head);
						exit(exit_status);
					}
					waitpid(pid, &status, 0); // Protect 'waitpid' output
					g_glob.exit_status = WEXITSTATUS(status);
				}
			}
		}
		else if (node->token == HAREDOC)
		{
			here_doc_(node->data);
			in_fd = open(".tmp", O_RDWR, 00777);
		}
		node = node->next;
	}
	reset_stds_fd();
	return (0);
}

/* -------------------------------------------------------------------------- */