/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:04:04 by ikhelil           #+#    #+#             */
/*   Updated: 2025/08/16 13:00:18 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	parent_exec_signals_begin(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void parent_exec_signals_end(void)
{
	setup_signals_interactive();
}