/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:25:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 12:08:11 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	exit_errors(char *arg, t_shell *shell)
{
	if (!arg)
	{
		shell->status = 1;
		ft_putstr_fd("minishishishi: exit: too many arguments\n", 2);
	}
	else
	{
		shell->status = 2;
		ft_putstr_fd("minishishishi: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

void	env_errors(t_shell *shell, char *arg)
{
	shell->status = 1;
	ft_putstr_fd("minishishishi: env: ", 2);
	if (!arg)
		ft_putstr_fd("No environment variables set\n", 2);
	else if (arg[0] == '-' && ft_strlen(arg) > 1)
		ft_putstr_fd("no options managed\n", 2);
	else
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	export_errors(t_shell *shell, char *arg)
{
	shell->status = 1;
	ft_putstr_fd("minishishishi: ", 2);
	if (!arg)
		ft_putstr_fd("export: no options managed\n", 2);
	else
	{
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
}

void	redir_errors(t_tree *tree, t_shell *shell, char *source, char *msg)
{
	if (!ft_strcmp(tree->content, "<<"))
		return ;
	shell->status = 1;
	ft_putstr_fd("minishishishi: ", 2);
	ft_putstr_fd(source, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd("No such file or directory\n", 2);
	ft_putstr_fd("\n", 2);
}

void	history_errors(t_shell *shell, char *source, int count)
{
	ft_putstr_fd("minishishishi: history: ", 2);
	shell->status = 1;
	if (!source && count == 0)
		ft_putstr_fd("no options managed\n", 2);
	else if (!source && count == 1)
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(source, 2);
		if (count == 0)
			ft_putstr_fd(": numeric argument required\n", 2);
		else if (count == 1)
			ft_putstr_fd(": invalid option\n", 2);
	}
}
