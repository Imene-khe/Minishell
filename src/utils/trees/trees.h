/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:54:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/20 17:34:50 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H

# include "../../../include/minishell.h"
# include "../../../include/structs.h"

t_tree	*tree_new(char *content, int type);
void	add_leaf(t_tree **root, t_tree **leaf, int direction);
void	free_tree(t_tree *tree);
void	print_tree(t_tree *node, int depth);
int		count_elm(t_tree *tree, int type);
char	*tree_to_str(t_tree *tree, char *str, int sp);

int		in_tree(char *str, t_tree *tree);

#endif