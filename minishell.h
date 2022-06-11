/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:32:20 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 13:40:49 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ------------------------------- LIBRARIES -------------------------------- */

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <curses.h>
# include <stdio.h>
# include <fcntl.h>
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
	DOUBLEQ,
	SINGELQ,
	COMMAND,
	PIPE,
}	t_flags;

typedef enum e_error {
	no,
	yes
}	t_error;

// ----------- STRUCTs ---------- //
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	struct s_node	*next;
	int				token;
	char			*data;
	char			*path;
}	t_node;

typedef struct s_cmds
{
	int		token;
	char	*data;
	char	*path;
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

/* --------------------------------- PROTOTYPES ----------------------------- */
int		lexer_start(t_info *info);
int		parcer(char *str, t_info *info);

#endif
