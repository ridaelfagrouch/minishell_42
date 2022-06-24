/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:02:51 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 13:56:24 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

int	check_special(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			if (str[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

/* -------------------------------------------------------------------------- */

int	not_operator(t_info *info, int i)
{
	if (info->input[i] != PIPE && info->input[i] != IN && \
		info->input[i] != OUT && info->input[i] != APPEND && \
		info->input[i] != HAREDOC && info->input[i] != ' ')
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	init_rev(t_reverse *rev)
{
	rev->i = -1;
	rev->k = 0;
	ft_bzero(rev->word, 20);
	ft_bzero(rev->bef_pipe, 50);
	ft_bzero(rev->aft_pipe, 50);
}

/* -------------------------------------------------------------------------- */

void	removechar2(char *str, char chartoremmove, int k)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove && i == k)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}

/* -------------------------------------------------------------------------- */

char	*remove_red_in(char *str , int flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (flag == 0)
		{
			if (str[i] == IN && str[i + 1] == OUT)
			{
				removechar2(str, str[i + 1], i + 1);
				remove_red_in(str, flag);
			}
		}
		if (flag == 1)
		{
			if (str[i] == '<' && str[i + 1] == '>')
			{
				removechar2(str, str[i + 1], i + 1);
				remove_red_in(str, flag);
			}
		}
		i++;
	}
	return (str);
}

/* -------------------------------------------------------------------------- */

void	reverse_input(t_info *info)
{
	t_reverse	rev;

	info->input = remove_red_in(info->input, 0);
	rev.word = (char *)malloc(20);
	rev.bef_pipe = (char *)malloc(50);
	rev.aft_pipe = (char *)malloc(50);
	init_rev(&rev);
	while (info->input[++(rev.i)])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if ((info->input[rev.i] == IN || info->input[rev.i] == OUT || \
			info->input[rev.i] == APPEND || info->input[rev.i] == HAREDOC) && \
			rev.i != 0)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 20);
			ft_bzero(rev.bef_pipe, 50);
			ft_bzero(rev.aft_pipe, 50);
			continue ;
		}
	}
	free(rev.word);
	free(rev.bef_pipe);
	free(rev.aft_pipe);
}

/* -------------------------------------------------------------------------- */
