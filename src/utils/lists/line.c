/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:23:15 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 16:32:12 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

t_line	*line_new(char *content, int type, int nb)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->content = custom_strdup(content);
	if (!new->content)
		return (free(new), NULL);
	new->type = type;
	new->nb = nb;
	new->next = NULL;
	return (new);
}

void    line_add_back(t_line **head, t_line **new)
{
	t_line  *current;

    if (!new)
		return ;
    if (!*head)
	{
		*head = *new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = *new;
}

void	line_free(t_line *head)
{
	if (!head)
		return ;
	if (head->next)
		line_free(head->next);
	free(head->content);
	free(head);
}

int	line_size(t_line *line)
{
	int		size;
	t_line	*current;

	size = 0;
	current = line;
	while (current)
	{
		current = current->next;
		size++;
	}
	return (size);
}
