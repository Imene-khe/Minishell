/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:38:44 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 17:43:43 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_prio(t_line *line)
{
	if (line->type == PIPE)
		return (3);
	if (line->type == REDIR_IN || line->type == REDIR_OUT)
		return (2);
	if (line->type == CMD)
		return (1);
	if (line->type == ARG)
		return (0);
	return (-1);
}

static void	decide(t_line *line, t_tree *tree, t_line *actual, int limit)
{
	tree->right = tree_new(actual->next->content, actual->next->type);
	tree->left = transform(line, count_prio(actual), limit, actual->nb);
}

static t_tree	*args_recursive(t_line *line, int limit)
{
	t_tree	*args;
	t_tree	*branch;
	t_line	*current;
	int		i;

	i = 0;
	current = line;
	args = NULL;
	while (current && current->nb < limit)
	{
		if (count_prio(current) == 0)
		{
			branch = tree_new(current->content, current->type);
			if (!branch)
				return (free_tree(args), NULL);
			if (i == 0)
				add_leaf(&args, &branch, 0);
			else
				add_leaf(&args, &branch, 2);
			i++;
		}
		current = current->next;
	}
	return (args);
}

t_tree	*transform(t_line *line, int prio, int limit, int exclude)
{
	t_tree	*tree;
	t_line	*current;

	if (prio <= 0 || !line)
		return (NULL);
	current = line;
	while (current && current->nb <= exclude && exclude != -1)
		current = current->next;
	while (current && current->next && current->nb < limit
		&& count_prio(current) != prio)
		current = current->next;
	if (!current || current->nb >= limit || count_prio(current) != prio)
		return (transform(line, prio - 1, limit, -1));
	tree = tree_new(current->content, current->type);
	if (!tree)
		return (NULL);
	if (count_prio(current) == 3)
		tree->left = transform(line, prio, current->nb, exclude);
	if (count_prio(current) == 3)
		tree->right = transform(current->next, prio, limit, exclude);
	if (count_prio(current) == 2)
		decide(line, tree, current, limit);
	if (count_prio(current) == 1)
		tree->right = args_recursive(line, limit);
	return (tree);
}
