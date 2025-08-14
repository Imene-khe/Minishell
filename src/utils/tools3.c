/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:34:30 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/14 15:05:06 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	until_sep(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

char	**cmnd_split(char *path, t_tree *args, t_exec *ex)
{
	char	**cmnd;

	path = tree_to_str(args, path, 1);
	if (!path)
		return (NULL);
	cmnd = ft_split(path, ' ');
	free(path);
	if (!cmnd)
		clear_exit(ex->tree, ex, 1, "cmnd_split");
	return (cmnd);
}

void	modify_var(t_exec *ex, char *name, char *value, char *other)
{
	t_env	*env;
	t_env	*curr;

	env = ex->shell->envp;
	if (!env || !name)
		return (free(value));
	curr = env_find(env, name);
	if (curr)
	{
		if (curr->value)
			free(curr->value);
		if (value)
		{
			curr->value = ft_strdup(value);
			free(value);
			if (!curr->value && other)
				return (free(other), clear_exit(ex->tree, ex, 1, "modify_var"));
			else if (!curr->value)
				return (clear_exit(ex->tree, ex, 1, "modify_var"));
		}
		else
			curr->value = NULL;
	}
	else
		free(value);
}

int	too_big(char *str, int size)
{
	if (!str || size <= 0)
		return (1);
	if (size < 19)
		return (0);
	if (size > 19 || ((str[0] == '-' || str[0] == '+') && size > 20)
		|| ft_strcmp(str, "9223372036854775807") > 0
		|| ft_strcmp(str, "-9223372036854775808") > 0)
		return (1);
	return (0);
}

void	env_process(t_exec *ex, t_tree *args, int count, int *run)
{
	ex->pid[count] = fork();
	if (ex->pid[count] == -1)
		clear_exit(ex->tree, ex, 2, "fork()");
	if (ex->pid[count] == 0)
	{
		setup_signals_child();
		exec_cmd(args, ex, count, run);
	}
	else
		reset_pipe(ex, count);
	ex->in_env = 0;
	ex->need_fork = 0;
}
