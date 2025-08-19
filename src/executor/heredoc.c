/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhelil <ikhelil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:13:42 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/19 18:51:25 by ikhelil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc_loop(char *buff, t_heredoc *hd, t_exec *ex);
int		verify_heredoc(
			t_exec *ex, char **buff, t_heredoc *hd, const char *delim);
char	*expand_buff(char *buff, int pip[2], t_exec *ex);

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

int	manage_heredoc(t_tree *tree, t_exec *ex)
{
	char		*buff;
	t_heredoc	*hd;
	int			ret;
	int			r;

	hd = ft_calloc(1, sizeof(t_heredoc));
	if (!hd)
		return (clear_exit(ex->tree, ex, 1, "heredoc-hd"), -1);
	if (pipe(hd->pip) < 0)
		return (free(hd), clear_exit(tree, ex, 1, "pipe"), -1);
	buff = NULL;
	setup_signals_heredoc(&hd->old_sigint, &hd->old_sigquit);
	g_signal = 0;
	while (1)
	{
		r = verify_heredoc(ex, &buff, hd, tree->right->content);
		if (r < 0)
			return (restore_signals(hd->old_sigint, hd->old_sigquit),
				free(buff), close_fds(hd->pip), free(hd), -1);
		if (r == 1 || ft_strcmp(buff, tree->right->content) == 0)
			break ;
		heredoc_loop(buff, hd, ex);
	}
	restore_signals(hd->old_sigint, hd->old_sigquit);
	ret = hd->pip[0];
	return (free(buff), close(hd->pip[1]), free(hd), ret);
}

/*static int	close_and_free(t_exec *ex, t_heredoc *hd, int status, int ret)
{
	ex->shell->status = status;
	restore_signals(hd->old_sigint, hd->old_sigquit);
	close_fds(hd->pip);
	free(hd);
	return (ret);
}*/

int	verify_heredoc(t_exec *ex, char **buff, t_heredoc *hd, const char *delim)
{
	(void)hd;
	*buff = readline("> ");
	if (!*buff)
	{
		if (g_signal == SIGINT)
			return (ex->shell->status = 130, -1);
		print_heredoc_warning((char *)delim);
		ex->shell->status = 0;
		return (1);
	}
	if (g_signal == SIGQUIT)
	{
		free(*buff);
		*buff = NULL;
		ex->shell->status = 0;
		return (-1);
	}
	return (0);
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
