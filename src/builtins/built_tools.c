/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:54:07 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/18 19:14:56 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_verify(t_tree *args)
{
	if (count_elm(args, ARG) == 0 || (count_elm(args, ARG) == 1
			&& !ft_strcmp(args->content, "~")))
		return (1);
	return (0);
}

int	change_directory(t_exec *ex, char *old, char *var)
{
	char	*val;

	val = NULL;
	val = ft_getenv(ex->shell->envp, var);
	if (chdir(val) == -1)
	{
		if (val)
			free(val);
		return (free(old), cd_errors(ex->shell, var, 2), -1);
	}
	free(val);
	return (0);
}
