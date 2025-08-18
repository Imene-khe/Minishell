/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:14:52 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/18 17:12:05 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "signals.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../../include/structs.h"

extern int	g_signal;

// Signals
void	sigint_interactive(int signo);
void	setup_signals_interactive(void);
void	setup_signals_child(void);
int		interpret_wait_status(int wstatus, int i);

// Signals 2
void	parent_exec_signals_begin(void);
void	parent_exec_signals_end(void);
void	sigint_heredoc(int signo);
void	sigquit_heredoc(int signo);
void	setup_signals_heredoc(void(**old_sigint)(int), void(**old_sigquit)(int));
void	restore_signals(void (*old_sigint)(int), void (*old_sigquit)(int));

#endif
