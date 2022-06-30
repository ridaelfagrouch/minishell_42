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
// Libraries: Functions
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

// Libraries: Macros and Data-Types
# include <stdbool.h>
# include <limits.h>

// Libraries: Custom
// # include "../../libft/libft.h"
# include "../../minishell.h"
# include "../lexer/lexer.h"

/* --------------------------------- MACROS --------------------------------- */
# define BUILT_INS	"echo cd pwd export unset env exit"

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //
// !------------------------------------------------------------------------! //
// typedef enum e_flags {
// 	EXPAND = -38,
// 	OUT,
// 	IN,
// 	APPEND,
// 	HAREDOC,
// 	SEMICOLON,
// 	COMMAND,
// 	PIPE,
// 	SPACE_,
// 	DQ,
// 	SQ,
// }	t_flags;
// !------------------------------------------------------------------------! //

typedef enum e_pipe_stat
{
	NO_PIPE,
	TO_PIPE,
	FROM_PIPE,
}	t_pipe_stat;

// ----------- STRUCTs ---------- //

typedef struct s_execut
{
	int	in_fd;
	int	out_fd;
	int	pid;
	int	exit_status;
	int	status;
	int	pipe_fd[2];
}	t_execut;

// !------------------------------------------------------------------------! //
// typedef struct s_node
// {
// 	struct s_node	*next;
// 	int				token;
// 	char			*data;
// 	char			*path;
// 	int				file_fd;
// 	char			**cmd_split;
// }	t_node;

// typedef struct s_env_vars {
// 	char				*key;
// 	char				*value;
// 	struct s_env_vars	*next;
// }	t_env_vars;

// typedef struct s_glob_info
// {
// 	int			exit;
// 	int			d_stdout;
// 	int			d_stdin;
// 	pid_t		heredoc_pid;
// 	int			heredoc_fd;
// 	t_env_vars	**env_head;
// }	t_glob_info;

// typedef struct s_info
// {
// 	t_node			*head;
// }	t_info;

// t_glob_info	g_glob;
// !------------------------------------------------------------------------! //

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
int			execute_command(t_node *node, t_env_vars **env_vars);

// exec_misc.c
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);
void		print_err(char *cmd, char *input, char *msg);

// redirect_exec.c
int			reset_stds_fd(void);
int			redirect_input(int new_input_fd);
int			redirect_output(int new_output_fd);
int			store_stds(t_execut *execut);

void		free_two_dim_arr(char **sorted_env);




// int		handle_execution(t_info *usr_input, t_env_vars **env_head);
// void	handle_signals(void);
// t_env_vars	*conv_env(char **envp);
// int			process_env_var(t_env_vars **head, char *env_var);
// void	hide_ctrl(void);
// void	restore_ctrl(void);
// char	*get_wildcard_data(void);
// char	*get_env(const char *var, t_env_vars *env_head);


#endif
