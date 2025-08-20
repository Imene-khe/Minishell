/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:44:18 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 12:10:24 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	clear_exit(t_tree *tree, t_exec *ex, int code, char *source)
{
	if (code == 0 || code == 130)
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
		env_errors(ex->shell, source);
	else if (code == 226 || code == 227)
		code -= 100;
	else
		print_error("Unknown error", source);
	free_structs(tree, ex, 1);
	exit(code);
}

void	print_error(char *msg, char *source)
{
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
	if (code == 3)
	{
		ft_putstr_fd(line->content, 2);
		if (!ft_strcmp(line->content, "."))
			ft_putstr_fd(": filename argument required\n", 2);
		else
			ft_putstr_fd(": Is a directory\n", 2);
	}
}

void	cmnd_errors(char *cmnd, int count, int code, t_exec *ex)
{
	ft_putstr_fd("minishishishi: ", 2);
	ft_putstr_fd(cmnd, 2);
	if (code == 126)
	{
		if (count == 0)
			ft_putstr_fd(": Is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		clear_exit(ex->tree, ex, 226, cmnd);
	}
	if (code == 127)
	{
		if (count == 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		clear_exit(ex->tree, ex, 227, cmnd);
	}
}

void	cd_errors(t_shell *shell, char *file, int cwd)
{
	shell->status = 1;
	ft_putstr_fd("minishishishi: cd: ", 2);
	if (cwd == 1)
	{
		ft_putstr_fd("error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else if (!file)
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(file, 2);
		if (cwd == 2)
			ft_putstr_fd(" : not set\n", 2);
		else if (cwd == 3)
			ft_putstr_fd(" : Not a directory\n", 2);
		else if (cwd == 4)
			ft_putstr_fd(" : no option managed\n", 2);
		else
			ft_putstr_fd(" : No such file or directory\n", 2);
	}
}
