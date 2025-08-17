/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:31 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/17 18:29:07 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		opening(t_tree *tree, t_exec *ex, int *in, int *out);
void	assign_fd(t_exec *ex, int *fd_count, int in_out, int tmp_fd);
int		manage_heredoc(t_tree *tree, t_exec *ex);
char	*expand_buff(char *buff, int pip[2], t_exec *ex);

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
	char	*right_content;

	right_content = tree->right->content;
	if (tree->type == REDIR_IN)
	{
		if (ft_strcmp(tree->content, "<<") == 0)
			tmp_fd = manage_heredoc(tree, ex);
		else
			tmp_fd = open(right_content, O_RDONLY);
		if (tmp_fd < 0)
			return (redir_errors(ex->shell, right_content, "No such file or directory"), 0);
		assign_fd(ex, in, 0, tmp_fd);
	}
	else if (tree->type == REDIR_OUT)
	{
		if (ft_strcmp(tree->content, ">>") == 0)
			tmp_fd = open(right_content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			tmp_fd = open(right_content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp_fd < 0)
			return (redir_errors(ex->shell, right_content, "No such file or directory"), 0);
		assign_fd(ex, out, 1, tmp_fd);
	}
	return (1);
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

int	manage_heredoc(t_tree *tree, t_exec *ex)
{
	int		pip[2];
	char	*buff;

	if (pipe(pip) < 0)
		clear_exit(tree, ex, 1, "pipe");
	buff = NULL;
	while (ft_strcmp(buff, tree->right->content) != 0)
	{
		if (buff)
		{
			buff = expand_buff(buff, pip, ex);
			if (write(pip[1], buff, ft_strlen(buff)) < 0
				|| write(pip[1], "\n", 1) < 0)
				return (free(buff), close_fds(pip),
					clear_exit(tree, ex, 1, "write"), -1);
			free(buff);
		}
		buff = readline("> ");
		if (!buff)
			return (ex->shell->status = 130, close(pip[1]), free(buff), -1);
	}
	close(pip[1]);
	return (free(buff), pip[0]);
}

char	*expand_buff(char *buff, int pip[2], t_exec *ex)
{
	char	*expanded;

	expanded = expand(buff, ex->shell, 0);
	free(buff);
	if (!expanded)
		return (close_fds(pip),
			clear_exit(ex->tree, ex, 1, "expand"), NULL);
	return (expanded);
}
