/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:13:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/19 18:13:33 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc_loop(char *buff, t_heredoc *hd, t_exec *ex);
int		verify_heredoc(t_exec *ex, char **buff, t_heredoc *hd);
char	*expand_buff(char *buff, int pip[2], t_exec *ex);

int	manage_heredoc(t_tree *tree, t_exec *ex)
{
	char		*buff;
	t_heredoc	*hd;
	int ret;

	hd = ft_calloc(sizeof(t_heredoc), 1);
	if (!hd)
		return (clear_exit(ex->tree, ex, 1, "heredoc-hd"), -1);
	if (pipe(hd->pip) < 0)
		return (free(hd), clear_exit(tree, ex, 1, "pipe"), -1);
	buff = NULL;
	setup_signals_heredoc(&hd->old_sigint, &hd->old_sigquit);
	g_signal = 0;
	while (ft_strcmp(buff, tree->right->content) != 0)
	{
		if (buff)
			heredoc_loop(buff, hd, ex);
		if (verify_heredoc(ex, &buff, hd) < 0)
			return (-1);
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

int	verify_heredoc(t_exec *ex, char **buff, t_heredoc *hd)
{
	*buff = readline("> ");
	if (!*buff)
	{
		close_fds(hd->pip);
		restore_signals(hd->old_sigint, hd->old_sigquit);
		free(hd);
		clear_exit(ex->tree, ex, 0, "Heredoc");
		return (-1);
	}
	if (g_signal == SIGINT || g_signal == SIGQUIT)
	{
		if (*buff)
			free(*buff);
		ex->shell->status = 130;
		if (g_signal == SIGQUIT)
		{
			ex->shell->status = 0;
		}
		restore_signals(hd->old_sigint, hd->old_sigquit);
		return (close_fds(hd->pip), free(hd), free(buff), -1);
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
