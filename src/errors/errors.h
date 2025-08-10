/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:44:10 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/08 19:32:04 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "../../include/minishell.h"

void	clear_exit(t_tree *tree, t_exec *ex, int code, char *source);
void	print_error(char *msg, char *source);
void	line_errors(t_line *line, int code);
void	cd_errors(t_shell *shell, char *file, int cwd);
void	exit_errors(char *arg);
void	env_errors(t_shell *shell, char *arg);

#endif
