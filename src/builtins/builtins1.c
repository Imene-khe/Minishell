/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:48:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/12 15:01:16 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_next(t_tree *args, t_exec *ex, char *old);

int	builtins(t_tree *tree, t_exec *ex, int count, int *run)
{
	if (!ft_strcmp(tree->content, "echo"))
		return (echo(tree->right, ex), ex->shell->status = 0, 1);
	if (!ft_strcmp(tree->content, "pwd"))
		return (pwd(ex), 1);
	if (!ft_strcmp(tree->content, "env"))
		return (env(tree->right, ex, count, run), 1);
	if (!ft_strcmp(tree->content, "cd"))
		return (cd(tree->right, ex), 1);
	if (!ft_strcmp(tree->content, "unset"))
		return (unset(tree->right, ex->shell), 1);
	if (!ft_strcmp(tree->content, "export"))
		return (export(tree->right, ex->shell, ex), 1);
	if (!ft_strcmp(tree->content, "exit"))
		return (exit_built(tree->right, ex, run), 1);
	return (0);
}

void	echo(t_tree *args, t_exec *ex)
{
	char	*strarg;
	t_tree	*curr;

	if (args)
	{
		strarg = NULL;
		curr = args;
		while (curr && curr->content[0] == '-'
			&& is_allchar(curr->content + 1, 'n'))
			curr = curr->right;
		strarg = tree_to_str(curr, strarg, 0);
		if (strarg)
		{
			printf("%s", strarg);
			free(strarg);
		}
		if (ft_strcmp(args->content, "-n") && curr == args)
			printf("\n");
	}
	else
		printf("\n");
	ex->shell->status = 0;
}

void	pwd(t_exec *ex)
{
	char	*buff;

	buff = malloc(PATH_SIZE);
	if (!buff)
		clear_exit(ex->tree, ex, 1, "pwd");
	buff = getcwd(buff, PATH_SIZE);
	if (!buff)
		return (free(buff), ex->shell->status = 1,
			ft_putstr_fd("pwd: error retrieving current directory.\n", 2));
	printf("%s\n", buff);
	free(buff);
	ex->shell->status = 0;
}

void	cd(t_tree *args, t_exec *ex)
{
	char	*old;
	char	*val;

	ex->shell->status = 0;
	if (count_elm(args, ARG) > 1)
		return (cd_errors(ex->shell, NULL, 0));
	old = NULL;
	old = getcwd(old, PATH_SIZE);
	if (!old)
		return (cd_errors(ex->shell, NULL, 1));
	if (cd_verify(args))
	{
		val = ft_getenv(ex->shell->envp, "HOME");
		if (!val || chdir(val) == -1)
			return (free(old), cd_errors(ex->shell, "HOME", 2));
	}
	else if (count_elm(args, ARG) == 1 && !ft_strcmp(args->content, "-"))
	{
		val = ft_getenv(ex->shell->envp, "OLDPWD");
		if (!val || chdir(val) == -1)
			return (free(old), cd_errors(ex->shell, "OLDPWD", 2));
	}
	else if (chdir(args->content) == -1)
		return (free(old), cd_errors(ex->shell, args->content, 0));
	cd_next(args, ex, old);
}

void	cd_next(t_tree *args, t_exec *ex, char *old)
{
	char	*new;

	new = NULL;
	new = getcwd(new, PATH_SIZE);
	if (!new)
		return (free(new), free(old), cd_errors(ex->shell, NULL, 1));
	if (count_elm(args, ARG) == 1 && !ft_strcmp(args->content, "-"))
		printf("%s\n", new);
	modify_var(ex, "OLDPWD", old, new);
	modify_var(ex, "PWD", new, NULL);
}
