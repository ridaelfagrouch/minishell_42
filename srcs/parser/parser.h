/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:50:09 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 15:50:13 by mnaimi           ###   ########.fr       */
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


/* --------------------------------- PROTOTYPES ----------------------------- */
int		check_special(char *str, int c);
int		check_syntax2(char *str);
int		check_operator(t_info *info, int flag);
void	store_data(t_info *info);
void	handel_command(t_info *info, t_cmds *cmds, char *str);
void	handel_out(t_info *info, t_cmds *cmds, char *str);
void	handel_herdoc(t_info *info, t_cmds *cmds, char *str);
void	handel_in(t_info *info, t_cmds *cmds, char *str);
void	handel_pipe(t_info *info, t_cmds *cmds);
void	while_operator(t_info *info, char *str);
void	scape_space(t_info *info);
void	add_back(t_node **lst, t_node *node);
t_node	*new_node(t_cmds *cmds);
#endif
