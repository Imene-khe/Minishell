/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:48:36 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/08 19:35:42 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../../include/minishell.h"

int		builtins(t_tree *tree, t_exec *ex, int count, int *run);
void	echo(t_tree *args, t_exec *ex);
void	pwd(t_exec *ex);
void	cd(t_tree *args, t_exec *ex);

void	env(t_tree *args, t_exec *ex, int count, int *run);
void	unset(t_tree *arg, t_shell *shell);
void	export(t_tree *args, t_shell *shell);
void	exit_built(t_tree *args, t_exec *ex, int *run);

void	export_noargs(t_shell *shell);
void	export_args(t_tree *args, t_shell *shell);

#endif
