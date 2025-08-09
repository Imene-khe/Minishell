/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:47:29 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/24 11:30:00 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*join_value(char **arr, int size, t_env *curr);

void	env_delete(t_env *head, t_env *target)
{
	t_env	*curr;
	t_env	*prev;

	curr = head;
	prev = NULL;
	while (curr)
	{
		if (curr == target)
		{
			if (curr == head)
				head = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_env	*arr_to_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;
	int		j;

	if (!envp || !*envp)
		return (NULL);
	head = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		new = env_new(envp[i]);
		if (!new)
			return (env_free(head),
				print_error("Malloc failed", "env"), exit(1), NULL);
		env_add_back(&head, new);
	}
	return (head);
}

char	**env_to_arr(t_env *env)
{
	char	**arr;
	int		size;
	t_env	*curr;

	arr = ft_calloc(sizeof(char *), env_size(env) + 1);
	if (!arr)
		return (NULL);
	curr = env;
	size = -1;
	while (curr)
	{
		arr[++size] = ft_strdup(curr->name);
		if (!arr[size])
			return (free_arr(arr, size), NULL);
		if (curr->value)
		{
			arr[size] = join_value(arr, size, curr);
			if (!arr[size])
				return (free_arr(arr, size), NULL);
		}
		curr = curr->next;
	}
	return (arr);
}

char	*join_value(char **arr, int size, t_env *curr)
{
	arr[size] = altered_ft_strjoin(arr[size], "=");
	if (!arr[size])
		return (free_arr(arr, size), NULL);
	arr[size] = altered_ft_strjoin(arr[size], curr->value);
	if (!arr[size])
		return (free_arr(arr, size), NULL);
	return (arr[size]);
}

char	*ft_getenv(t_env *env, char *name)
{
	t_env	*curr;

	if (!env || !name)
		return (NULL);
	curr = env;
	while (curr && ft_strcmp(curr->name, name))
		curr = curr->next;
	if (curr)
		return (curr->value);
	return (NULL);
}
