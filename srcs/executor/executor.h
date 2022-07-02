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

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ------------------------------- LIBRARIES -------------------------------- */
// Functions
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>

// Macros and Data-Types
# include <limits.h>

// Custom
# include "../../minishell.h"
# include "../lexer/lexer.h"

/* --------------------------------- MACROS --------------------------------- */
# define BUILT_INS		"echo cd pwd export unset env exit"
# define HEREDOC_PATH	"/tmp/mshell_heredoc_"

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ STRUCTs ----------- //
typedef struct s_exec
{
	int	def_std_in;
	int	def_std_out;
	int	input;
	int	output;
	int	pipe[2];
	int	file_err;
}	t_exec;

/* --------------------------------- PROTOTYPES ----------------------------- */
// env_init_2nd.c
int			set_default_pwd(t_env_vars **head);
int			set_shell_lvl(t_env_vars **head);
void		free_env_linked_list(t_env_vars *head);
void		free_env(t_env_vars *head);

// env_init_1st.c
t_env_vars	*conv_env(char **envp);
int			process_env_var(t_env_vars **head, char *env_var);

// builtin_cmds
int			cd_cmd(char **input, t_env_vars **env_head);
int			echo_cmd(char **input, t_env_vars **env_head);
int			export_cmd(char **input, t_env_vars **env_head);
int			unset_cmd(char **input, t_env_vars **env_head);
int			env_cmd(char **input, t_env_vars **env_head);
int			pwd_cmd(char **input, t_env_vars **env_head);
void		exit_cmd(char **input, t_env_vars **env_head);

// exec_cmds.c
int			execute_builtins(char **input, t_env_vars **env_vars);
int			execute_command(t_node *node, t_env_vars **env_vars);

// exec_misc.c
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);
void		print_err(char *cmd, char *input, char *msg);

// redirect_exec.c
void		redirect_input(int new_input_fd);
void		redirect_output(int new_output_fd);

void		free_double_pointer(char **sorted_env);
void		ignore_signal(void);

#endif
