/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:51:01 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/08 19:18:02 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	waiting(t_tree *tree, t_exec *ex)
{
	int	i;
	int	count;
	int	status;

	i = 0;
	count = count_elm(tree, CMD);
	while (i < count)
	{
		if (ex->pid[i] != -1)
		{
			waitpid(ex->pid[i], &status, 0);
			if (WIFEXITED(status))
				ex->shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ex->shell->status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	execution(t_exec *ex, int fds[2], char **cmnd, char **env)
{
	if (execve(cmnd[0], cmnd, env) < 0)
	{
		close_fds(fds);
		clear_exit(ex->tree, ex, 127, "execve");
	}
}

void	dups(t_exec *ex, int fd, int fds[2], int dupped)
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
	if (curr && ft_strcmp(curr->content, "cd") && ft_strcmp(curr->content, "unset")
		&& ft_strcmp(curr->content, "export") && ft_strcmp(curr->content, "exit")
		&& ft_strcmp(curr->content, "env") && ft_strcmp(curr->content, "pwd")
		&& ft_strcmp(curr->content, "echo"))
		return (1);
	return (0);
}
