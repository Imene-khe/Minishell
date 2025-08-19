/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:48:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/18 19:24:41 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_next(t_tree *args, t_exec *ex, char *old);

int	builtins(t_tree *tree, t_exec *ex, int count, int *run)
{
	if (!ft_strcmp(tree->content, "echo"))
		return (echo(tree->right, ex), 1);
	if (!ft_strcmp(tree->content, "pwd"))
		return (pwd(ex, tree->right), 1);
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
	if (!ft_strcmp(tree->content, "history"))
		return (built_history(ex->shell->history,
				&(ex->shell), tree->right), 1);
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

void	pwd(t_exec *ex, t_tree *arg)
{
	char	*buff;

	ex->shell->status = 0;
	if (arg && arg->content[0] == '-' && ft_strlen(arg->content) > 1)
	{
		ex->shell->status = 1;
		ft_putstr_fd("minishishishi: ", 2);
		ft_putstr_fd(arg->content, 2);
		ft_putstr_fd(": invalid option\n", 2);
		return ;
	}
	buff = NULL;
	buff = getcwd(buff, PATH_SIZE);
	if (!buff)
	{
		ft_putstr_fd("pwd: error retrieving current directory.\n", 2);
		ex->shell->status = 1;
	}
	else
		printf("%s\n", buff);
	free(buff);
}

void	cd(t_tree *args, t_exec *ex)
{
	char	*old;
	char	*new;

	ex->shell->status = 0;
	if (count_elm(args, ARG) > 1)
		return (cd_errors(ex->shell, NULL, 0));
	old = NULL;
	old = getcwd(old, PATH_SIZE);
	if (!old)
		return (cd_errors(ex->shell, NULL, 1));
	if (cd_next(args, ex, old) < 0)
		return ;
	new = NULL;
	new = getcwd(new, PATH_SIZE);
	if (!new)
		return (free(new), free(old), cd_errors(ex->shell, NULL, 1));
	if (count_elm(args, ARG) == 1 && !ft_strcmp(args->content, "-"))
		printf("%s\n", new);
	modify_var(ex, "OLDPWD", old, new);
	modify_var(ex, "PWD", new, NULL);
}

int	cd_next(t_tree *args, t_exec *ex, char *old)
{
	struct stat	st;

	if (args && args->content && args->content[0] == '-' && ft_strlen(args->content) > 1)
		return (cd_errors(ex->shell, args->content, 4), -1);
	if (cd_verify(args))
		return (change_directory(ex, old, "HOME"));
	else if (count_elm(args, ARG) == 1 && !ft_strcmp(args->content, "-"))
		return (change_directory(ex, old, "OLDPWD"));
	else if (stat(args->content, &st) >= 0 && !S_ISDIR(st.st_mode))
		cd_errors(ex->shell, args->content, 3);
	else if (chdir(args->content) == -1)
		return (free(old), cd_errors(ex->shell, args->content, 0), -1);
	return (0);
}
