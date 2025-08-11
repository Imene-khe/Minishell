/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:14:52 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 14:14:53 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
extern int  g_signal;
void        setup_signals_interactive(void);
void	setup_signals_child(void);
int		interpret_wait_status(int wstatus);


#endif
