/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:15:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 19:45:37 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**parse_for_paths(t_env *env, t_exec *ex)
{
	t_env	*curr;
	char	**paths;

	curr = env;
	while (curr && ft_strcmp(curr->name, "PATH"))
		curr = curr->next;
	if (!curr)
		return (NULL);
	paths = ft_split(curr->value, ':');
	if (!paths)
		return (clear_exit(ex->tree, ex, 1, "split"), NULL);
	return (paths);
}
