/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:53 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/13 15:19:42 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* ------------------------------- LIBRARIES -------------------------------- */
# include "../../minishell.h"
# include <string.h>

/* --------------------------------- MACROS --------------------------------- */


/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //


// ----------- STRUCTs ---------- //

typedef struct expand
{
	char		*result;
	char		*ptr;
	char		*str;
	int			check;
	size_t		i;
	size_t		cnt;
	size_t		newlen;
	size_t		oldlen;
}	t_expand;


/* --------------------------------- PROTOTYPES ----------------------------- */
void	new_quote(t_quote **quotes, int i, int on, int class);
void	in_out(char *input, int *i, t_quote	*quotes);
int		check_dollar(t_info *info, int i, t_quote *quotes);
void	unclosed_quotes(t_quote *quotes, t_info *info);
void	free_quotes(t_quote *quotes);
void	d_quotes(t_quote **quotes, char *input, int i, int *check);
void	s_quotes(t_quote **quotes, char *input, int i, int *check);
int		quoted(t_quote *quotes, int i);
void	handle_quotes(t_quote **quotes, char *quote, int i, int *check);
char	*input_expand(t_info *info);

#endif
