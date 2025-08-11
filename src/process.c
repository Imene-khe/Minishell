/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:09:41 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 15:47:05 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prep_exec(t_tree *tree, int *run, t_shell *shell);
int		verify_line(t_line *line, t_line *head, int prio);

void	treatment(char *prompt, int *run, t_shell *shell)
{
	t_line	*line;
	t_tree	*tree;

	add_history(prompt);
	if (closed(prompt))
	{
		line = lexer(prompt, shell);
		free(prompt);
		if (!line)
			return (free_shell(shell),
				print_error("Malloc failed", "lexer"), exit(1));
		if (!verify_line(line, line, 2))
			return (line_free(line));
		tree = transform(line, 3, line_size(line), -1);
		line_free(line);
		if (!tree)
			return (free_shell(shell),
				print_error("Malloc failed", "tree"), exit(1));
		prep_exec(tree, run, shell);
	}
	else
		free(prompt);
}

void	prep_exec(t_tree *tree, int *run, t_shell *shell)
{
	t_exec	*ex;

	ex = malloc(sizeof(t_exec));
	if (!ex)
		clear_exit(tree, NULL, 1, "exec");
	ex = init_exec(tree, ex, shell);
	if (count_elm(tree, PIPE) > 0)
	{
		if (pipe(ex->pipe1) < 0)
			clear_exit(tree, ex, 5, "pipe1");
		if (pipe(ex->pipe2) < 0)
			clear_exit(tree, ex, 5, "pipe2");
		ex->need_pipe = 1;
	}
	pre_exec(tree, ex, run);
	waiting(tree, ex);
	free_structs(tree, ex, 0);
}

int	verify_line(t_line *line, t_line *head, int prio)
{
	int	ret;

	if (!line && prio != 1)
		return (verify_line(head, head, prio - 1));
	if (!line)
		return (1);
	ret = 1;
	if (prio == 2 && line->type == PIPE)
	{
		if (line->nb == 0 && line->type == PIPE)
			return (line_errors(line, 1), 0);
		if (!line->next)
			return (line_errors(line, 2), 0);
	}
	if (prio == 2 && (line->type == REDIR_IN || line->type == REDIR_OUT))
		if ((line->next && line->next->type != FILE) || !line->next)
			return (line_errors(line->next, 1), 0);
	if (prio == 1 && line->type == CMD)
		if (is_dir(line->content))
			return (line_errors(line, 3), 0);
	ret = verify_line(line->next, head, prio);
	return (ret);
}
