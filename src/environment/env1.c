/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:41:23 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 16:23:57 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_new(char *var)
{
	t_env	*new;

	if (!var)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_substr(var, 0, ft_strchr(var, '=') - var);
	if (!new->name)
		return (free(new), NULL);
	if (until_sep(var, '=') == (int)ft_strlen(var))
		new->value = NULL;
	else
	{
		new->value = ft_strdup(var + (ft_strchr(var, '=') - var) + 1);
		if (!new->value)
			return (free(new->name), free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*current;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	env_free(t_env *head)
{
	if (!head)
		return ;
	if (head->next)
		env_free(head->next);
	free(head->name);
	free(head->value);
	free(head);
}

t_env	*env_find(t_env *head, char *name)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	env_size(t_env *env)
{
	int		size;
	t_env	*current;

	size = 0;
	current = env;
	while (current)
	{
		current = current->next;
		size++;
	}
	return (size);
}
