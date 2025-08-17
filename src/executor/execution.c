/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:51:01 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 13:57:56 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../signals/signals.h"

void	waiting(t_exec *ex)
{
	int	i;
	int	count;
	int	status;

	i = 0;
	status = 0;
	count = ex->cmd_count;
	while (i < count)
	{
		if (ex->pid[i] != -1)
		{
			waitpid(ex->pid[i], &status, 0);
			if (WIFEXITED(status))
				ex->shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ex->shell->status = 128 + WTERMSIG(status);
			ex->shell->status = interpret_wait_status(status, i);
		}
		i++;
	}
}

void	execution(t_exec *ex, int fds[4], char **cmnd, char **env)
{
	if (execve(cmnd[0], cmnd, env) < 0)
	{
		close_fds(fds);
		clear_exit(ex->tree, ex, 127, "execve");
	}
}

void	dups(t_exec *ex, int fd, int fds[4], int dupped)
{
	if (dup2(fd, dupped) < 0)
	{
		close_fds(fds);
		clear_exit(ex->tree, ex, 10, "dup2");
	}
}

int	need_fork(t_exec *ex, t_tree *tree)
{
	t_tree	*curr;

	if (ex->need_pipe)
		return (1);
	curr = tree;
	while (curr && curr->type != CMD)
		curr = curr->left;
	if (curr && ft_strcmp(curr->content, "cd")
		&& ft_strcmp(curr->content, "unset")
		&& ft_strcmp(curr->content, "export")
		&& ft_strcmp(curr->content, "exit")
		&& ft_strcmp(curr->content, "env")
		&& ft_strcmp(curr->content, "pwd")
		&& ft_strcmp(curr->content, "echo"))
		return (1);
	return (0);
}

int	forking(t_exec *ex, t_tree *tree, int count, int *run)
{
	ex->pid[count] = fork();
	if (ex->pid[count] == -1)
		clear_exit(ex->tree, ex, 2, "fork()");
	if (ex->pid[count] == 0)
	{
		setup_signals_child();
		exec(tree, ex, count, run);
		return (1);
	}
	else
		return (2);
	return (0);
}
