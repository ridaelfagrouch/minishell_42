/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:32:20 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/05/23 21:32:22 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <curses.h>
# include "../libft/libft.h"

# define PIPE -48
# define COMMAND -47
# define SINGELQ -46
# define DOUBLEQ -45
# define SEMICOLON -44
# define HAREDOC -43
# define APPEND -42
# define IN -41
# define OUT -40
# define SPACE -39
# define EXPAND -38
# define SPECIAL_ "|&<>"
# define WHITESPACE " \r\v\n\t\f"

typedef enum erreur{no, yes}	t_erreur;

typedef struct s_info
{
	char			*input;
	int				uncqu;
}	t_info;

typedef struct s_quote
{
	int				i;
	int				on;
	int				class;
	struct s_quote	*next;
}	t_quote;

int	lexer_start(t_info *info);
int	parcer(char *str, t_info *info);

#endif
