/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 21:37:48 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	handle_sig(int signum, siginfo_t *siginfo, void *sigcontext)
{
	(void)sigcontext;
	(void)siginfo;
	if (signum == SIGINT)
		write(STDIN_FILENO, "\n", 1);
}

/* -------------------------------------------------------------------------- */

void	handle_signals(void)
{
	struct sigaction	n_act[2];

	n_act[0].sa_sigaction = handle_sig;
	n_act[0].sa_flags = SA_SIGINFO | SA_RESTART | SA_RESETHAND;
	sigaction(SIGINT, &n_act[0], NULL);

	n_act[1].sa_handler = SIG_IGN;
	n_act[1].sa_flags = 0;
	sigaction(SIGQUIT, &n_act[1], NULL);
}

