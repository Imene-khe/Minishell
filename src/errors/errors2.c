/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:25:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 11:40:39 by bguerrou         ###   ########.fr       */
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
