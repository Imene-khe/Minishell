/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:38:50 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/23 13:27:43 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"
# include "../../include/structs.h"

t_tree	*transform(t_line *line, int prio, int limit, int exclude);

char	**parse_for_paths(t_env *env, t_exec *ex);

#endif
