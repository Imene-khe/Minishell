/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:13:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/20 12:08:53 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc_loop(char *buff, t_heredoc *hd, t_exec *ex);
int		verify_heredoc(t_tree *tree, t_exec *ex, char **buff, t_heredoc *hd);
char	*expand_buff(char *buff, int pip[2], t_exec *ex);

int	manage_heredoc(t_tree *tree, t_exec *ex)
{
	char		*buff;
	t_heredoc	*hd;
	int			ret;

	hd = ft_calloc(sizeof(t_heredoc), 1);
	if (!hd)
		return (clear_exit(ex->tree, ex, 1, "heredoc-hd"), -1);
	if (pipe(hd->pip) < 0)
		return (free(hd), clear_exit(tree, ex, 1, "pipe"), -1);
	hd->backup = -1;
	if (!ex->need_fork)
		hd->backup = dup(0);
	buff = NULL;
	setup_signals_heredoc(&hd->old_sigint, &hd->old_sigquit);
	g_signal = 0;
	while (ft_strcmp(buff, tree->right->content) != 0)
	{
		if (buff)
			heredoc_loop(buff, hd, ex);
		if (verify_heredoc(tree, ex, &buff, hd) < 0)
			return (reopen(hd->backup), free(hd), -1);
	}
	restore_signals(hd->old_sigint, hd->old_sigquit);
	ret = hd->pip[0];
	return (free(buff), close(hd->pip[1]), free(hd), ret);
}

void	heredoc_loop(char *buff, t_heredoc *hd, t_exec *ex)
{
	buff = expand_buff(buff, hd->pip, ex);
	if (write(hd->pip[1], buff, ft_strlen(buff)) < 0
		|| write(hd->pip[1], "\n", 1) < 0)
		return (free(buff), close_fds(hd->pip),
			restore_signals(hd->old_sigint, hd->old_sigquit), free(hd),
			clear_exit(ex->tree, ex, 500, "write"));
	free(buff);
}

int	verify_heredoc(t_tree *tree, t_exec *ex, char **buff, t_heredoc *hd)
{
	*buff = readline("> ");
	if (!*buff)
	{
		if (g_signal == 0)
		{
			print_heredoc_warning(ex->tree->right->content);
			*buff = ft_strdup(tree->right->content);
			if (!*buff)
				return (close_fds(hd->pip),
					restore_signals(hd->old_sigint, hd->old_sigquit),
					free(hd), clear_exit(ex->tree, ex, 1, "heredoc-buff"), -1);
			return (1);
		}
		ex->shell->status = 130;
		close_fds(hd->pip);
		restore_signals(hd->old_sigint, hd->old_sigquit);
		if (ex->need_fork)
		{
			free(hd);
			clear_exit(ex->tree, ex, ex->shell->status, "Heredoc");
		}
		return (-1);
	}
	return (0);
}

char	*expand_buff(char *buff, int pip[2], t_exec *ex)
{
	char	*expanded;

	expanded = expand(buff, ex->shell, NULL, 0);
	free(buff);
	if (!expanded)
		return (close_fds(pip),
			clear_exit(ex->tree, ex, 1, "expand"), NULL);
	return (expanded);
}
