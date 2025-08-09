/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:31:22 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/21 14:20:18 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trees.h"

int	in_tree(char *str, t_tree *tree)
{
	t_tree	*current;

	if (!tree || !str)
		return (0);
	current = tree;
	while (current)
	{
		if (!ft_strncmp(current->content, str, ft_strlen(current->content)))
			return (1);
		current = current->right;
	}
	return (0);
}


