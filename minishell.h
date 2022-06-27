/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:32:20 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 10:52:05 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "libft/libft.h"

/* --------------------------------- MACROS --------------------------------- */
// COLOR CODES //
# define NNN	"\033[0m"
# define RED	"\033[31m"
# define GRN	"\033[32m"
# define YEL	"\033[33m"
# define BLU	"\033[34m"
# define MGN	"\033[35m"
# define CYN	"\033[36m"
# define GRA	"\033[37m"

# define SPECIAL_		"|&<>;"
# define WHITESPACE		" \r\v\n\t\f"

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //
typedef enum e_flags {
	EXPAND = -38,
	OUT,
	IN,
	APPEND,
	HAREDOC,
	SEMICOLON,
	COMMAND,
	PIPE,
	SPACE_,
}	t_flags;

typedef enum e_error {
	no,
	yes
}	t_error;

// ----------- STRUCTs ---------- //
typedef struct s_env_vars {
	char				*key;
	char				*value;
	struct s_env_vars	*next;
}	t_env_vars;

typedef struct s_node
{
	struct s_node	*next;
	int				token;
	char			*data;
	char			*path;
	int				file_fd;
	char			**cmd_split;
}	t_node;

typedef struct s_cmds
{
	int		token;
	char	*data;
	char	*path;
	int		i;
	int		j;
	int		file_fd;
}	t_cmds;

typedef struct s_info
{
	char			*input;
	int				uncqu;
	int				i;
	t_node			*head;
	t_cmds			*cmds;
}	t_info;

typedef struct s_quote {
	int				i;
	int				on;
	int				class;
	struct s_quote	*next;
}	t_quote;

typedef struct d_data
{
	char		**path_split;
	char		*path;
	char		**cmd_split;
	char		*cmd;
	char		*final_path;
	int			i;
	int			check_access;
	char		*ptr;
}	t_data;

typedef struct s_glob_info
{
	u_int8_t		exit;
	int				pipe_fd[2];
	int				d_stdout;
	int				d_stdin;
	sig_atomic_t	sig_heredoc;
	pid_t			heredoc_pid;
}	t_glob_info;

t_glob_info	g_glob;

/* --------------------------------- PROTOTYPES ----------------------------- */
int		lexer_start(t_info *info);
int		parcer(char *str, t_info *info);

int		handle_execution(t_info *usr_input, t_env_vars **env_head);
void	handle_signals(void);
t_env_vars	*conv_env(char **envp);
int			process_env_var(t_env_vars **head, char *env_var);
void	hide_ctrl(void);
void	restore_ctrl(void);
char	*get_wildcard_data(void);
//void	handle_sig(int signum, siginfo_t *siginfo, void *sigcontext);

#endif
