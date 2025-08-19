/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:34:36 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/19 17:06:43 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	manage_pipes(t_tree *tree, t_exec *ex, int *run)
{
	pre_exec(tree->left, ex, run);
	pre_exec(tree->right, ex, run);
}

void	reset_pipe(t_exec *ex, int count)
{
	int	which;

	which = 0;
	if (count % 2 != 0 && ex->need_pipe)
		which = 1;
	else if (ex->need_pipe)
		which = 2;
	if (which == 1)
	{
		close_fds(ex->pipe1);
		if (pipe(ex->pipe1) < 0)
			clear_exit(ex->tree, ex, 5, "pipe1");
	}
	else if (which == 2)
	{
		close_fds(ex->pipe2);
		if (pipe(ex->pipe2) < 0)
			clear_exit(ex->tree, ex, 5, "pipe2");
	}
}

void	set_fds(t_exec *ex, t_tree *tree, int count)
{
	if (count == 0 && (ex->write_fd == 1 || count_elm(tree, CMD) == 0))
	{
		close(ex->pipe1[0]);
		close_fds(ex->pipe2);
		ex->write_fd = ex->pipe1[1];
	}
	else if (count % 2 != 0)
		pair_pipe(ex, count, ex->pipe1, ex->pipe2);
	else if (count % 2 == 0)
		pair_pipe(ex, count, ex->pipe2, ex->pipe1);
}

void	pair_pipe(t_exec *ex, int count, int pipe1[2], int pipe2[2])
{
	close(pipe1[1]);
	if (ex->read_fd == 0)
		ex->read_fd = pipe1[0];
	else
		close(pipe1[0]);
	close(pipe2[0]);
	if (ex->write_fd == 1 && count != count_elm(ex->tree, PIPE))
		ex->write_fd = pipe2[1];
	else
		close(pipe2[1]);
}
