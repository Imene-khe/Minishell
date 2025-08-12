/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:31:07 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/12 14:31:08 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trees.h"

t_tree	*tree_new(char *content, int type)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!(new->content))
		return (free(new), NULL);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	add_leaf(t_tree **root, t_tree **leaf, int direction)
{
	t_tree	*current;

	current = *root;
	if (direction == 0)
		*root = *leaf;
	else if (direction == 1)
	{
		while (current->left)
			current = current->left;
		current->left = *leaf;
	}
	else if (direction == 2)
	{
		while (current->right)
			current = current->right;
		current->right = *leaf;
	}
}

void	free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree->content);
	free(tree);
}

int	count_elm(t_tree *tree, int type)
{
	int	count;

	count = 0;
	if (!tree)
		return (count);
	if (tree->left)
		count += count_elm(tree->left, type);
	if (tree->right)
		count += count_elm(tree->right, type);
	if (tree->type == type)
		count++;
	return (count);
}

char	*tree_to_str(t_tree *tree, char *str, int sp)
{
	t_tree	*curr;

	curr = tree;
	while (curr)
	{
		if (sp++ != 0)
		{
			str = new_strjoin(str, " ");
			if (!str)
				return (NULL);
		}
		str = new_strjoin(str, curr->content);
		if (!str)
			return (NULL);
		curr = curr->right;
	}
	return (str);
}
