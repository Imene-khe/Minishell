/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:58 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/23 17:07:00 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../include/minishell.h"

char	*expand(char *str, t_shell *shell);

int	    till_sep(char *str);
int	    change_mode(char c, int *mode);
char	*var_name(char *str);

#endif