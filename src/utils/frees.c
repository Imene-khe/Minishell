/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:17:14 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/27 17:00:59 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_structs(t_tree *tree, t_exec *ex, int s)
{
	if (s)
		free_shell(ex->shell);
	free_tree(tree);
	if (ex)
		free_exec(ex);
}

void	free_shell(t_shell *shell)
{
	if (shell->envp)
		env_free(shell->envp);
	free(shell);
}

void	free_exec(t_exec *exec)
{
	exec->shell = NULL;
	if (exec->paths)
		free_arr(exec->paths, arr_size(exec->paths));
	if (exec->pid)
		free(exec->pid);
	if (exec->read_fd != 0)
		close(exec->read_fd);
	if (exec->write_fd != 1)
		close(exec->write_fd);
	if (exec->need_pipe)
	{
		close_fds(exec->pipe1);
		close_fds(exec->pipe2);
	}
	free(exec);
}

void	close_fds(int *fds)
{
	int i;

	i = 0;
	while (i < 2)
		if (fds[i] != 0 && fds[i] != 1)
			close(fds[i++]);
}
