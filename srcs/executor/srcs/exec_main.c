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

/* -------------------------------------------------------------------------- *\
TODO-[X]
\* -------------------------------------------------------------------------- */

void	command_handler(t_node *head, t_node *node, t_exec *exec, \
	t_env_vars **env_head)
{
	if (node->next && node->next->token == PIPE)
		pipe_handler(node, exec);
	if (exec->output == -1)
		exec->output = dup(exec->def_std_out);
	if (exec->input == -1)
		exec->input = dup(exec->def_std_in);
	redirect_input(exec->input);
	redirect_output(exec->output);
	if (ft_strstr_tl(BUILT_INS, node->cmd_split[0]) && !is_multiple_pipes(head))
		g_glob.exit = execute_builtins(node->cmd_split, env_head);
	else
		g_glob.exit = execute_command(exec, node, env_head);
	exec->input = dup(exec->def_std_in);
	exec->output = dup(exec->def_std_out);
	redirect_input(exec->input);
	redirect_output(exec->output);
	exec->input = -1;
	exec->output = -1;
}

/* -------------------------------------------------------------------------- *\
TODO-[X]	Don't free the filenames, only free the array of pointers
\* -------------------------------------------------------------------------- */

int	convert_heredoc_to_file(t_node *head)
{
	t_node	*node;
	char	**file_names;
	int		count;

	count = count_heredocs(head);
	if (count == 0)
		return (0);
	file_names = name_heredoc_files(count);
	if (!file_names || !file_names[0])
		return (free_double_pointer(file_names), -1);
	while (count--)
	{
		node = get_first_heredoc_node(head);
		if (!node)
			return (free_double_pointer(file_names), -1);
		heredoc_handler(node->data, file_names[count]);
		node->file_fd = open(file_names[count], O_RDONLY);
		if (node->file_fd < 0)
			print_err(NULL, "heredoc", "internal error detected");
		free(node->data);
		node->data = file_names[count];
		node->token = IN;
		node->cmd_flag = 69;
	}
	return (free(file_names), 0);
}

/* -------------------------------------------------------------------------- *\
TODO-[]	Free all allocated memory
TODO-[]	The last four lines should be in a function called after 
TODO		the execution
TODO-[]	Do not free t_info, also t_node, but do close the file FDs
TODO	  and unlink the files
\* -------------------------------------------------------------------------- */

int	handle_execution(t_info *parsed_data, t_env_vars **env_head)
{
	t_exec	exec;

	if (set_def_values(&exec) < 0)
		return (-1);
	handle_signals();
	convert_heredoc_to_file(parsed_data->head);
	exec.node = parsed_data->head;
	while (exec.node)
	{
		if ((exec.node->token == IN || exec.node->token == OUT || \
			exec.node->token == APPEND) && is_invalid_file_fd(&exec.node))
			continue ;
		else if (exec.node->token == IN)
			input_handler(&exec.node, &exec);
		else if (exec.node->token == OUT || exec.node->token == APPEND)
			output_handler(&exec.node, &exec);
		else if (exec.node->token == COMMAND)
			command_handler(parsed_data->head, exec.node, &exec, env_head);
		else if (exec.node->token == PIPE)
			pipe_handler(exec.node, &exec);
		exec.node = exec.node->next;
	}
	restore_def_values(&exec, parsed_data->head);
	return (0);
}
