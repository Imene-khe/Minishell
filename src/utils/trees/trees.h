/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:54:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 17:52:50 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H

# include "../../../include/minishell.h"
# include "../../../include/structs.h"

// Tree 1
t_tree	*tree_new(char *content, int type);
void	add_leaf(t_tree **root, t_tree **leaf, int direction);
void	free_tree(t_tree *tree);
int		count_elm(t_tree *tree, int type);
char	*tree_to_str(t_tree *tree, char *str, int sp);

// Tree 2
int		in_tree(char *str, t_tree *tree);

#endif