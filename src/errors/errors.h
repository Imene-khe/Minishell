/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:44:10 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 11:42:48 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "../../include/minishell.h"

// Errors 1
void	clear_exit(t_tree *tree, t_exec *ex, int code, char *source);
void	print_error(char *msg, char *source);
void	line_errors(t_line *line, int code);
void	cmnd_errors(char *cmnd, int count, int code, t_exec *ex);
void	cd_errors(t_shell *shell, char *file, int cwd);

// Errors 2
void	exit_errors(char *arg, t_shell *shell);
void	env_errors(t_shell *shell, char *arg);
void	export_errors(t_shell *shell, char *arg);
void	redir_errors(t_tree *tree, t_shell *shell, char *source, char *msg);
void	history_errors(t_shell *shell, char *source, int count);

#endif
