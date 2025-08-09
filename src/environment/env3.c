/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:36:44 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/23 17:07:30 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_dup(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(env->name);
	if (!new->name)
		return (free(new), NULL);
	if (env->value)
	{
		new->value = ft_strdup(env->value);
		if (!new->value)
			return (free(new->name), free(new), NULL);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
