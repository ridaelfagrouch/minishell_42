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
	t_node	*node;
	int		def_std_in;
	int		def_std_out;
	int		input;
	int		output;
	int		pipe[2];
	int		file_err;
	int		status;
}	t_exec;

/* --------------------------------- PROTOTYPES ----------------------------- */
// env_init_2nd.c
int			set_default_pwd(t_env_vars **head);
int			set_shell_lvl(t_env_vars **head);

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
int			execute_command(t_exec *exec, t_node *node, t_env_vars **env_vars);

// exec_misc_1.c
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);
void		free_two_dim_arr(char **sorted_env);
void		print_err(char *cmd, char *input, char *msg);
char		*put_expand(char *ptr);
int			is_mult_pipes(t_node *node);

// exec_misc_2.c
void		free_double_pointer(char **ptr);
void		free_linked_list(t_node *head);
int			count_command_nodes(t_node *head);
void		unlink_heredoc_files(t_node *head);
void		close_fds(t_node *head);

// exec_misc_3.c
void		restore_def_values(t_exec *exec, t_node *head);
int			set_def_values(t_exec *exec);
int			check_invalid_command(t_node *head);
int			is_invalid_file_fd(t_node **head);

// exec_main.c
void		command_handler(t_node *head, t_node *node, t_exec *exec, \
	t_env_vars **env_head);
int			convert_heredoc_to_file(t_node *head);
int			handle_execution(t_info *parsed_data, t_env_vars **env_head);

// redir_and_pipe.c
void		redirect_input(int new_input_fd);
void		redirect_output(int new_output_fd);
void		output_handler(t_node **node, t_exec *exec);
void		input_handler(t_node **node, t_exec *exec);
void		pipe_handler(t_node *node, t_exec *exec);

// heredoc_handler.c
void		heredoc_filler(int heredoc, char *delimiter);
int			heredoc_handler(char *delimiter, char *filename);
t_node		*get_first_heredoc_node(t_node *head);
int			count_heredocs(t_node *head);
char		**name_heredoc_files(int count);

// signal_handling.c
void		hide_ctrl(void);
void		restore_ctrl(void);
void		ignore_signal(void);
void		handle_sig(int signum, siginfo_t *siginfo, void *sigcontext);
void		handle_signals(void);

#endif
