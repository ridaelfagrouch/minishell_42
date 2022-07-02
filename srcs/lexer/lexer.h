/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:53 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/24 15:51:14 by rel-fagr         ###   ########.fr       */
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
typedef struct reverse
{
	size_t	i;
	size_t	j;
	size_t	t;
	size_t	k;
	size_t	ls;
	size_t	lw;
	int		start;
	char	*word;
	char	*ptr;
	char	*bef_pipe;
	char	*aft_pipe;
}	t_reverse;

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

typedef struct replace
{
	int		i;
	int		cnt;
	int		len1;
	int		len2;
	int		k;
	char	*newstring;
	char	*ptr;
}	t_replace;

/* --------------------------------- PROTOTYPES ----------------------------- */
void	new_quote(t_quote **quotes, int i, int on, int class);
void	in_out(char *input, int *i, t_quote	*quotes);
int		check_dollar(t_info *info, int i, t_quote *quotes);
void	unclosed_quotes(t_quote *quotes, t_info *info);
void	free_quotes(t_quote *quotes);
void	d_quotes(t_quote **quotes, int i, int *check, char *input);
void	s_quotes(t_quote **quotes, int i, int *check, char *input);
int		quoted(t_quote *quotes, int i);
void	handle_quotes(t_quote **quotes, char *quote, int i, int *check);
char	*input_expand(char *input);
void	reverse_input(t_info *info);
void	reverse_input_plus(t_info *info);
int		check_special(char *str, int c);
void	set_rev(t_reverse *rev, t_info *info);
void	check_rev(t_reverse *rev, t_info *info);
int		not_operator(t_info *info, int i);
void	free_reverse(t_reverse	*rev);
char	*replaceword2(char *text, char *old, char *new, int start);
void	expanding(t_expand *expd, char *s, char *old, char *new);
void	remp_bef_aft_pipe(t_info *info, char *bef_pipe, char *aft_pipe, int k);
char	*remove_red_in(char *str);

#endif
