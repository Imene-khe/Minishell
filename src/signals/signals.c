/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:30:55 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 23:47:49 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int	g_signal = 0;

static void	sigint_interactive(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	setup_signals_interactive(void)
{
	signal(SIGINT, sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	interpret_wait_status(int wstatus)
{
	int	sig;

	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
	{
		sig = WTERMSIG(wstatus);
		if (sig == SIGQUIT)
			write(2, "Quit\n", 5);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		return (128 + sig);
	}
	return (0);
}
