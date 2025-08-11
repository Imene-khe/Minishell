/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:14:57 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 14:15:05 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

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

static void	ignore_handler(int signo)
{
	(void)signo;
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_interactive;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ignore_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	interpret_wait_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
	{
		int	sig = WTERMSIG(wstatus);

		if (sig == SIGQUIT)
			write(2, "Quit\n", 5);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		return (128 + sig);
        // pour le recup et savoir on arrete notre truc avec quelle manip
	}
	return (0);
}

