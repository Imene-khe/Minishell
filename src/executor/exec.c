/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:52:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 22:48:43 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../signals/signals.h"


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

int	exec(t_tree *tree, t_exec *ex, int count, int *run)
{
	t_tree	*curr;
	int		in;
	int		out;

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
