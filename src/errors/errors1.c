/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:44:18 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 13:40:32 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	cmnd_errors(char *cmnd);

void	clear_exit(t_tree *tree, t_exec *ex, int code, char *source)
{
	if (code == 0)
		code += 0;
	else if (code == 1)
		print_error("Malloc failed", source);
	else if (code == 2)
		print_error("Fork failed", source);
	else if (code == 4)
		print_error("Couldn't execute", source);
	else if (code == 5)
		print_error("Pipe failed", source);
	else if (code == 127)
		cmnd_errors(source);
	else
		print_error("Unknown error", source);
	free_structs(tree, ex, 1);
	exit(code);
}

void	print_error(char *msg, char *source)
{
	if (!ft_strcmp(msg, "No such file or directory")
		|| !ft_strcmp(msg, "Cannot open file"))
	{
		ft_putstr_fd("minishishishi: ", 2);
		ft_putstr_fd(source, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(source, 2);
	ft_putstr_fd(" - ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	line_errors(t_line *line, int code)
{
	ft_putstr_fd("minishishishi: ", 2);
	if (code == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (line)
			ft_putstr_fd(line->content, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
	}
	if (code == 2)
		ft_putstr_fd("Uncompleted pipe\n", 2);
}

void	cmnd_errors(char *cmnd)
{
	ft_putstr_fd("minishishishi: ", 2);
	ft_putstr_fd(cmnd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	cd_errors(t_shell *shell, char *file, int cwd)
{
	if (cwd)
		ft_putstr_fd("minishishishi: cd: error retrieving current directory\n", 2);
	else if (!file)
		ft_putstr_fd("minishishishi: cd: too many arguments\n", 2);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	shell->status = 1;
}

void	exit_errors(char *arg)
{
	if (!arg)
		ft_putstr_fd("minishishishi: exit: too many arguments\n", 2);
	else
	{
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
