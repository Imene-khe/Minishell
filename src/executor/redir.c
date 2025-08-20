/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:31 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 12:08:28 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		opening(t_tree *tree, t_exec *ex, int *in, int *out);
int		open_files(t_tree *tree, t_exec *ex, int count, char *cont);
void	assign_fd(t_exec *ex, int *fd_count, int in_out, int tmp_fd);

int	try_open(t_tree *tree, t_exec *ex, int *in, int *out)
{
	int	ret;

	ret = 1;
	if (tree->type == REDIR_IN || tree->type == REDIR_OUT)
	{
		if (ex->in_redirs == 0)
			ex->in_redirs = count_elm(tree, REDIR_IN);
		if (ex->out_redirs == 0)
			ex->out_redirs = count_elm(tree, REDIR_OUT);
		ret = opening(tree, ex, in, out);
		if (ret && tree->left)
			ret = try_open(tree->left, ex, in, out);
	}
	return (ret);
}

int	opening(t_tree *tree, t_exec *ex, int *in, int *out)
{
	int		tmp_fd;
	char	*r;

	r = tree->right->content;
	if (tree->type == REDIR_IN)
	{
		if (ft_strcmp(tree->content, "<<") && !access(r, F_OK)
			&& access(r, R_OK) != 0)
			return (redir_errors(tree, ex->shell, r, "Permission denied"), 0);
		tmp_fd = open_files(tree, ex, 1, r);
		if (tmp_fd < 0)
			return (redir_errors(tree, ex->shell, r, NULL), 0);
		assign_fd(ex, in, 0, tmp_fd);
	}
	else if (tree->type == REDIR_OUT)
	{
		if (access(r, F_OK) == 0 && access(r, W_OK) != 0)
			return (redir_errors(tree, ex->shell, r, "Permission denied"), 0);
		tmp_fd = open_files(tree, ex, 2, r);
		if (tmp_fd < 0)
			return (redir_errors(tree, ex->shell, r, NULL), 0);
		assign_fd(ex, out, 1, tmp_fd);
	}
	return (1);
}

int	open_files(t_tree *tree, t_exec *ex, int count, char *cont)
{
	int	tmp_fd;

	tmp_fd = 0;
	if (count == 1)
	{
		if (ft_strcmp(tree->content, "<<") == 0)
			tmp_fd = manage_heredoc(tree, ex);
		else
			tmp_fd = open(cont, O_RDONLY);
	}
	else if (count == 2)
	{
		if (ft_strcmp(tree->content, ">>") == 0)
			tmp_fd = open(cont, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			tmp_fd = open(cont, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (tmp_fd);
}

void	assign_fd(t_exec *ex, int *fd_count, int in_out, int tmp_fd)
{
	if (in_out == 0)
	{
		if (++(*fd_count) == ex->in_redirs)
			ex->read_fd = tmp_fd;
		else
			close(tmp_fd);
	}
	if (in_out == 1)
	{
		if (++(*fd_count) == ex->out_redirs)
			ex->write_fd = tmp_fd;
		else
			close(tmp_fd);
	}
}
