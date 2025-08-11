/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:52:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/10 20:12:57 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../signals/signals.h"


void	manage_pipes(t_tree *tree, t_exec *ex, int *run);
void	reset_pipe(t_exec *ex, int which);
void	set_fds(t_exec *ex, int count);
void	pair_pipe(t_exec *ex, int count, int pipe1[2], int pipe2[2]);

t_exec	*init_exec(t_tree *tree, t_exec *exec, t_shell *shell)
{
	exec->tree = tree;
	exec->cmd_count = 0;
	exec->shell = shell;
	exec->paths = NULL;
	exec->pid = NULL;
	exec->need_pipe = 0;
	exec->need_fork = 0;
	exec->read_fd = 0;
	exec->write_fd = 1;
	exec->in_redirs = 0;
	exec->out_redirs = 0;
	exec->in_env = 0;
	exec->paths = parse_for_paths(shell->envp, exec);
	exec->pid = custom_calloc(sizeof(int), count_elm(tree, CMD) + 1, -1);
	if (!exec->pid)
		clear_exit(exec->tree, exec, 1, "exec-pid");
	return (exec);
}

int	pre_exec(t_tree *tree, t_exec *ex, int *run)
{
	int	count;

	if (!tree || !ex)
		return (1);
	if (tree->type == PIPE)
		manage_pipes(tree, ex, run);
	else
	{
		count = (ex->cmd_count)++;
		ex->need_fork = need_fork(ex, tree);
		if (!ex->need_fork)
			return (exec(tree, ex, count, run));
		ex->pid[count] = fork();
		if (ex->pid[count] == -1)
			clear_exit(ex->tree, ex, 2, "fork()");
		if (ex->pid[count] == 0)
		{
			setup_signals_child();
			exec(tree, ex, count, run);
		}
		else
			reset_pipe(ex, count);
	}
	return (0);
}

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

int	exec(t_tree *tree, t_exec *ex, int count, int *run)
{
	t_tree	*curr;
	int	in;
	int	out;

	if (!tree || !ex)
		return (0);
	in = 0;
	out = 0;
	if (!try_open(tree, ex, &in, &out))
		return (2);
	if (ex->need_pipe)
		set_fds(ex, count);
	curr = tree;
	while (curr && curr->type != CMD)
		curr = curr->left;
	if (curr)
		exec_cmd(curr, ex, count, run);
	return (0);
}

void	set_fds(t_exec *ex, int count)
{
	if (count == 0 && ex->write_fd == 1)
	{
		close(ex->pipe1[0]);
		close_fds(ex->pipe2);
		ex->write_fd = ex->pipe1[1];
	}
	else if (count % 2 != 0)
		pair_pipe(ex, count, ex->pipe1, ex->pipe2);
	else
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
	if (ex->write_fd == 1 && count != count_elm(ex->tree, CMD) - 1)
		ex->write_fd = pipe2[1];
	else
		close(pipe2[1]);
}
