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

/* -------------------------------------------------------------------------- */

void	hide_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

/* -------------------------------------------------------------------------- */

void	restore_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

/* -------------------------------------------------------------------------- */

void	handle_sig(int signum, siginfo_t *siginfo, void *sigcontext)
{
	(void)sigcontext;
	if (signum == SIGINT && siginfo->si_signo == SIGINT)
	{
		if (g_glob.heredoc_pid == 0)
			exit(0);
		else if (g_glob.heredoc_pid != -1)
		{
			if (g_glob.heredoc_fd >= 0)
				close (g_glob.heredoc_fd);
			kill(g_glob.heredoc_pid, SIGTERM);
			unlink(".tmp");
			g_glob.heredoc_fd = -1;
			g_glob.heredoc_pid = -1;
		}
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
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

/* -------------------------------------------------------------------------- */
