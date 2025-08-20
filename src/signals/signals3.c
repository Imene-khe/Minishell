/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:01:49 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 12:12:57 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	setup_signals_heredoc(void (**old_sigint)(int),
	void (**old_sigquit)(int))
{
	*old_sigint = signal(SIGINT, sigint_heredoc);
	*old_sigquit = signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void (*old_sigint)(int), void (*old_sigquit)(int))
{
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
}

void	sigint_heredoc(int signo)
{
	(void) signo;
	g_signal = SIGINT;
	write(1, "\n", 1);
	close(0);
}

void	print_heredoc_warning(char *delim)
{
	write(2, "minishell: warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 34);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}

void	reopen(int backup)
{
	if (backup >= 0)
	{
		dup2(backup, 0);
		close(backup);
	}
}
