/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:22:01 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 16:14:26 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**set_command(char *cmnd, char **paths, t_tree *args, t_exec *ex);
void	reset_fds(t_exec *ex, int fds[4]);

int	exec_cmd(t_tree	*tree, t_exec *ex, int count, int *run)
{
	char	**cmnd;
	char	**env;
	int		fds[(4)];

	fds[0] = ex->read_fd;
	fds[1] = ex->write_fd;
	fds[2] = dup(0);
	fds[3] = dup(1);
	if (fds[0] != 0)
		dups(ex, fds[0], fds, 0);
	if (fds[1] != 1)
		dups(ex, fds[1], fds, 1);
	if (builtins(tree, ex, count, run))
	{
		if (ex->need_fork)
			clear_exit(ex->tree, ex, 0, "builtins");
		return (reset_fds(ex, fds), 0);
	}
	cmnd = set_command(tree->content, ex->paths, tree->right, ex);
	if (!cmnd)
		clear_exit(ex->tree, ex, 127, tree->content);
	env = env_to_arr(ex->shell->envp);
	execution(ex, fds, cmnd, env);
	return (0);
}

void	reset_fds(t_exec *ex, int fds[4])
{
	if (ex->read_fd != 0)
	{
		dups(ex, fds[2], fds, 0);
		close(ex->read_fd);
		ex->read_fd = 0;
	}
	if (ex->write_fd != 1)
	{
		dups(ex, fds[3], fds, 1);
		close(ex->write_fd);
		ex->write_fd = 1;
	}
}

char	**set_command(char *cmnd, char **paths, t_tree *args, t_exec *ex)
{
	char	*path;

	if (!ft_strncmp(cmnd, "", 1))
		return (NULL);
	if (!ft_strncmp(cmnd, "./", 2) && !access(cmnd, X_OK))
		return (cmnd_split(cmnd, args, ex));
	else if (!ft_strncmp(cmnd, "./", 2) && access(cmnd, X_OK) != 0)
		return (clear_exit(ex->tree, ex, 126, cmnd), NULL);
	while (*paths)
	{
		path = ft_strjoin(*(paths++), "/");
		if (!path)
			return (NULL);
		path = altered_ft_strjoin(path, cmnd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (cmnd_split(path, args, ex));
		free(path);
	}
	return (NULL);
}
