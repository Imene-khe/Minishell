/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:58 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 16:53:55 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../include/minishell.h"

char	*expand(char *str, t_shell *shell, int mode);

int	    till_sep(char *str);
int	    change_mode(char c, int *mode);
char	*var_name(char *str);

#endif