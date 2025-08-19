/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhelil <ikhelil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:38:35 by ikhelil           #+#    #+#             */
/*   Updated: 2025/08/19 18:32:28 by ikhelil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <stdlib.h>

void	print_heredoc_warning(char *delim)
{
	write(2, "minishell: warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 34);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}

void	restore_signals(void (*old_sigint)(int), void (*old_sigquit)(int))
{
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
}

int	handle_check(int check)
{
	if (check < 0)
		return (-1);
	if (check == 1)
		return (0);
	return (2);
}
