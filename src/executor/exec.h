/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:53:05 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/14 14:53:28 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../include/minishell.h"

// Exec
t_exec	*init_exec(t_tree *tree, t_exec *exec, t_shell *shell);
int		pre_exec(t_tree *tree, t_exec *ex, int *run);
int		exec(t_tree *tree, t_exec *ex, int count, int *run);
void	free_shell(t_shell *shell);

// Cmnds
int		exec_cmd(t_tree	*tree, t_exec *ex, int count, int *run);

// Redir
int		try_open(t_tree *tree, t_exec *ex, int *in, int *out);

// Pipe
void	manage_pipes(t_tree *tree, t_exec *ex, int *run);
void	reset_pipe(t_exec *ex, int which);
void	set_fds(t_exec *ex, int count);
void	pair_pipe(t_exec *ex, int count, int pipe1[2], int pipe2[2]);

// Execution
void	waiting(t_exec *ex);
void	execution(t_exec *ex, int fds[2], char **cmnd, char **env);
void	dups(t_exec *ex, int fd, int fds[2], int dupped);
int		need_fork(t_exec *ex, t_tree *tree);
int 	forking(t_exec *ex, t_tree *tree, int count, int *run);

#endif