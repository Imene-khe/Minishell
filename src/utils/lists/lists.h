/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:16 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/19 17:50:49 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "../../../include/minishell.h"
# include "../../../include/structs.h"

// Line
t_line	*line_new(char *content, int type, int nb);
void	line_add_back(t_line **head, t_line **new);
void	line_free(t_line *head);
int		line_size(t_line *line);
t_line	*line_last(t_line *head);

// Hisotry
void	ft_add_history(char *command, t_shell *shell);
void	built_history(t_history *history, t_shell **shell, t_tree *args);
void	history_free(t_history *history);

#endif