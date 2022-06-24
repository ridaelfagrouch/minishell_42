/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:50:09 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/24 15:57:50 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ------------------------------- LIBRARIES -------------------------------- */
# include "../../minishell.h"
# include "../lexer/lexer.h"

/* --------------------------------- MACROS --------------------------------- */

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //

// ----------- STRUCTs ---------- //

typedef struct syntax
{
	int		i;
	int		cout;
	char	check;
	int		dq;
}	t_syntax;

/* --------------------------------- PROTOTYPES ----------------------------- */
int		check_syntax2(char *str);
int		check_operator(t_info *info, int flag);
int		store_data(t_info *info);
int		handel_command(t_info *info, t_cmds *cmds, char *str);
void	handel_out(t_info *info, t_cmds *cmds, char *str);
void	handel_herdoc(t_info *info, t_cmds *cmds, char *str);
void	handel_in(t_info *info, t_cmds *cmds, char *str);
void	handel_pipe(t_info *info, t_cmds *cmds);
void	while_operator(t_info *info, char *str);
void	scape_space(t_info *info);
void	add_back(t_node **lst, t_node *node);
t_node	*new_node(t_cmds *cmds);
char	*get_path(char *av);
char	**ft_split_cmd(char *str);
int		check_builtins(char *str);
void	out_check_str(char *str, int i, t_cmds *cmds);
void	removechar(char *str, char chartoremmove);
int		check_builtins(char *str);
void	free_split(char **ptr);
char	*remove_dq_sq(char *str);
char	*check_str_cmd(char *str);
#endif
