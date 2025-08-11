/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:54:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 17:10:57 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_env(t_exec *ex);

void    env(t_tree *args, t_exec *ex, int count, int *run)
{
	ex->shell->status = 0;
	if (!ex->shell->envp)
		return (env_errors(ex->shell, NULL));
	else if (count_elm(args, ARG) >= 1)
	{
		ex->in_env = 1;
		if (args->content[0] == '-' && ft_strlen(args->content) > 1)
			return (env_errors(ex->shell, args->content));
		else
			ex->in_env = exec_cmd(args, ex, count, run);
		if (ex->in_env == 1)
			env_errors(ex->shell, args->content);
		ex->in_env = 0;
	}
	else
		print_env(ex);
}

void	print_env(t_exec *ex)
{
	t_env	*curr;

	curr = ex->shell->envp;
	while (curr)
	{
		if (curr->value)
			printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}

void	unset(t_tree *arg, t_shell *shell)
{
	shell->status = 0;
	if (!arg)
		return ;
	if (arg->content[0] == '-' && ft_strlen(arg->content) > 1)
	{
		shell->status = 1;
		printf("minishishishi: unset: no options managed\n");
	}
	else
		env_delete(shell->envp, env_find(shell->envp, arg->content));
}

void	export(t_tree *args, t_shell *shell, t_exec *ex)
{
	shell->status = 0;
	if (!args && shell->envp)
		export_noargs(shell, ex);
	else if (args)
	{
		if (args->content[0] == '-' && ft_strlen(args->content) > 1)
		{
			shell->status = 1;
			ft_putstr_fd("minishishishi: export: no options managed\n", 2);
		}
		else
			export_args(args, shell, ex);
	}
}

void	exit_built(t_tree *args, t_exec *ex, int *run)
{
	char	*first;

	if (!ex || !(ex->need_pipe))
	{
		*run = 0;
		ft_putstr_fd("exit\n", 2);
	}
	if (count_elm(args, ARG) >= 1)
	{
		first = args->content;
		if (!ft_isalldigit(first) || too_big(first, ft_strlen(first)))
			exit_errors(first);
		else if (count_elm(args, ARG) > 1)
		{
			exit_errors(NULL);
			*run = 1;
		}
		else
			ex->shell->status = ft_atoll(first) % 256;
	}
}
