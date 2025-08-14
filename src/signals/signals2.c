/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhelil <ikhelil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:04:04 by ikhelil           #+#    #+#             */
/*   Updated: 2025/08/14 19:08:17 by ikhelil          ###   ########.fr       */
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