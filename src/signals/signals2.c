/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:04:04 by ikhelil           #+#    #+#             */
/*   Updated: 2025/08/18 17:11:42 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	parent_exec_signals_begin(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	parent_exec_signals_end(void)
{
	setup_signals_interactive();
}

void	sigint_heredoc(int signo)
{
	(void) signo;
	g_signal = SIGINT;
	write(1, "\n", 1);
	close(0);
}

void	sigquit_heredoc(int signo)
{
	(void) signo;
}

void	setup_signals_heredoc(void(**old_sigint)(int), void(**old_sigquit)(int))
{
	*old_sigint = signal(SIGINT, sigint_heredoc);
	*old_sigquit = signal(SIGQUIT, sigquit_heredoc);
}

void	restore_signals(void (*old_sigint)(int), void (*old_sigquit)(int))
{
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
}
