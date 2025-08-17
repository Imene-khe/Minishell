/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:49:39 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/17 17:03:54 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	history_addback(t_history **history, t_history *new);
void	print_history(t_history *history, t_shell *shell, t_tree *arg);

void	ft_add_history(char *command, t_shell *shell)
{
	t_history	*new_node;

	new_node = malloc(sizeof(t_history));
	if (!new_node)
		return (free(command), free_shell(shell),
				print_error("Malloc failed", "history"), exit(1));
	new_node->command = ft_strdup(command);
	if (!new_node->command)
		return (free(new_node), free(command), free_shell(shell),
				print_error("Malloc failed", "history"), exit(1));
	history_addback(&shell->history, new_node);
	add_history(command);
}

void	history_addback(t_history **history, t_history *new)
{
	t_history	*curr;

	if (!*history)
	{
		*history = new;
		new->id = 1;
	}
	else
	{
		curr = *history;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->id = curr->id + 1;
	}
	new->next = NULL;
}

void	built_history(t_history *history, t_shell **shell, t_tree *args)
{
	t_history	*curr;

	(*shell)->status = 0;
	curr = history;
	if (count_elm(args, ARG) > 0)
	{
		if (ft_strcmp(args->content, "-c") == 0)
		{
			history_free((*shell)->history);
			(*shell)->history = NULL;
			clear_history();
			return ;
		}
		if (args->content[0] == '-' && ft_strlen(args->content) > 1)
			return (history_errors((*shell), NULL, 0));
		if (!ft_isalldigit(args->content) || too_big(args->content, ft_strlen(args->content)))
			return (history_errors((*shell), args->content, 0));
		if (count_elm(args, ARG) > 1)
			return (history_errors((*shell), NULL, 1));
	}
	print_history(history, (*shell), args);
}

void	print_history(t_history *history, t_shell *shell, t_tree *arg)
{
	int			count;
	int			max_count;
	t_history	*curr;

	if (!history)
		return ;
	curr = history;
	while (curr->next)
		curr = curr->next;
	max_count = curr->id;
	count = max_count + 1;
	if (arg)
		count = ft_atoll(arg->content);
	if (count < 0)
		history_errors(shell, arg->content, 1);
	curr = history;
	while (curr)
	{
		if (max_count - curr->id < count)
			printf("%d  %s\n", curr->id, curr->command);
		curr = curr->next;
	}
}

void	history_free(t_history *history)
{
	if (!history)
		return ;
	if (history->next)
		history_free(history->next);
	free(history->command);
	free(history);
}
