/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:15:42 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:52:23 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	free_quotes(t_quote *quotes)
{
	t_quote	*next;

	while (quotes)
	{
		next = quotes->next;
		free(quotes);
		quotes = next;
	}
}

/* -------------------------------------------------------------------------- */

void	free_reverse(t_reverse	*rev)
{
	free(rev->word);
	free(rev->bef_pipe);
	free(rev->aft_pipe);
}

/* -------------------------------------------------------------------------- */
