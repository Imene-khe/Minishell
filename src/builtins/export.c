/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:20:29 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/17 23:23:40 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*find_smallest(t_env *env, t_env **selected, int i);
void	print_export(t_env	*sorted_envp, t_shell *shell);
void	verify_export(t_tree *curr, t_shell *shell, t_exec *ex, char *name);

void	export_noargs(t_shell *shell, t_exec *ex)
{
	t_env	*sorted_envp;
	t_env	*smallest;
	t_env	**selected;
	int		i;
	int		size;

	size = env_size(shell->envp);
	selected = malloc(sizeof(t_env *) * size);
	if (!selected)
		return (shell->status = 1, clear_exit(ex->tree, ex, 1, "export"));
	i = 0;
	sorted_envp = NULL;
	while (i < size)
	{
		smallest = find_smallest(shell->envp, selected, i);
		selected[i++] = smallest;
		env_add_back(&sorted_envp, env_dup(smallest));
	}
	print_export(sorted_envp, shell);
	env_free(sorted_envp);
	free(selected);
}

t_env	*find_smallest(t_env *env, t_env **selected, int i)
{
	t_env	*smallest;
	t_env	*curr;
	int		j;

	smallest = NULL;
	curr = env;
	while (curr)
	{
		j = 0;
		while (j < i && selected[j] != curr)
			j++;
		if (j == i)
		{
			if (!smallest || ft_strcmp(curr->name, smallest->name) < 0)
				smallest = curr;
		}
		curr = curr->next;
	}
	return (smallest);
}

void	print_export(t_env *sorted_envp, t_shell *shell)
{
	t_env	*curr;

	curr = sorted_envp;
	while (curr)
	{
		printf("export %s", curr->name);
		if (ft_getenv(shell->envp, curr->name))
			printf("=\"%s\"\n", ft_getenv(shell->envp, curr->name));
		else
			printf("\n");
		curr = curr->next;
	}
}

void	export_args(t_tree *args, t_shell *shell, t_exec *ex)
{
	t_tree	*curr;
	char	*name;
	long	size;

	curr = args;
	while (curr)
	{
		name = NULL;
		size = until_sep(curr->content, '=');
		name = ft_strndup(curr->content, size);
		if (!name)
			return (shell->status = 1, clear_exit(ex->tree, ex, 1, "export"));
		if (!ft_isallalnum(name) || (size >= 1 && ft_isdigit(name[0]))
			|| size == 0)
			export_errors(shell, curr->content);
		else
			verify_export(curr, shell, ex, name);
		free(name);
		curr = curr->right;
	}
}

void	verify_export(t_tree *curr, t_shell *shell, t_exec *ex, char *name)
{
	t_env	*tmp;

	tmp = env_find(shell->envp, name);
	if (!tmp)
		env_add_back(&shell->envp, env_new(curr->content));
	else
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		if (until_sep(curr->content, '=') < (int)ft_strlen(curr->content))
		{
			tmp->value = ft_strdup(ft_strchr(curr->content, '=') + 1);
			if (!tmp->value)
				return (shell->status = 1,
					clear_exit(ex->tree, ex, 1, "export"));
		}
	}
}
