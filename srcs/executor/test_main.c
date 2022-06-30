/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 19:22:37 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	t_node		arr[1];
	t_env_vars	*env_head;
	t_info		user_input;


	arr[0].file_fd = -1;
	arr[0].path = ft_strdup("/bin/echo");
	arr[0].cmd_split = ft_split("env", ' ');
	arr[0].token = COMMAND;
	arr[0].next = NULL;
	user_input.head = &arr[0];
	(void)argc;
	(void)argv;
	env_head = conv_env(envp);
	handle_execution(&user_input, &env_head);
	free_env(env_head);
	free(arr[0].cmd_split[0]);
	free(arr[0].cmd_split[1]);
	free(arr[0].cmd_split);
	free(arr[0].path);
	return (0);
}

// ToDo:	Check commands exit status
// ToDo:	Check signal handling
// ToDo:	Check heredoc
// ToDo:	Check handle_execution function
// ToDo:	Check leaks
// ToDo:	Norm all the code 