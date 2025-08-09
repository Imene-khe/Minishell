/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:16 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/23 17:00:48 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "../../../include/minishell.h"
# include "../../../include/structs.h"

t_line	*line_new(char *content, int type, int nb);
void	line_add_back(t_line **head, t_line **new);
void	line_free(t_line *head);
int		line_size(t_line *line);

#endif