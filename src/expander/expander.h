/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:58 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/19 17:49:01 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../include/minishell.h"

char	*expand(char *str, t_shell *shell, t_line *line, int mode);

int		till_sep(char *str);
int		change_mode(char c, int *mode);
char	*var_name(char *str);

#endif