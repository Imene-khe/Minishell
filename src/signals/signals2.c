/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhelil <ikhelil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:04:04 by ikhelil           #+#    #+#             */
/*   Updated: 2025/08/19 18:03:57 by ikhelil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <stdlib.h>

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
	(void)signo;
	write(1, "\n", 1);
	exit(130);
}

void	sigquit_heredoc(int signo)
{
	(void)signo;
	write(1, "Quit (core dumped)\n", 19);
	exit(131);
}

void	setup_signals_heredoc(
		void (**old_sigint)(int), void (**old_sigquit)(int))
{
	*old_sigint = signal(SIGINT, sigint_heredoc);
	*old_sigquit = signal(SIGQUIT, sigquit_heredoc);
}
