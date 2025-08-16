/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:15:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 00:32:58 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_line	*lexer_next(char **split, int l[2], t_shell *shell);
int		check_type(char *str, int *t, int *s, int interpret);
t_line	*subsplit(char *str, int l[2], int *j, t_shell *shell);

t_line	*lexer(char *prompt, t_shell *shell)
{
	t_line	*head;
	char	**split;
	int		l[2];

	split = custom_split(prompt, ' ');
	if (!split)
		return (NULL);
	l[0] = 0;
	l[1] = 0;
	head = lexer_next(split, l, shell);
	free_arr(split, custom_countwords(prompt, ' '));
	if (!head)
		return (NULL);
	return (head);
}

t_line	*lexer_next(char **split, int l[2], t_shell *shell)
{
	t_line	*head;
	t_line	*current;
	int		i;
	int		j;
	char	*expanded;

	i = -1;
	j = 0;
	head = NULL;
	while (split[++i])
	{
		shell->quoted = 0;
		expanded = expand(split[i], shell, 0);
		if (!expanded)
			return (line_free(head), NULL);
		if (ft_countwords(expanded, ' ') <= 1 || l[1])
			current = line_new(expanded, check_type(expanded, &l[0], &l[1], 1), j++);
		else
			current = subsplit(expanded, l, &j, shell);
		free(expanded);
		if (!current)
			return (line_free(head), NULL);
		line_add_back(&head, &current);
	}
	return (head);
}

int	check_type(char *str, int *t, int *s, int interpret)
{
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (EMPTY);
	if (ft_strncmp(str, "|", len) == 0 && interpret)
		return (*t = 0, *s = 0, PIPE);
	if (ft_strncmp(str, "<<", len) == 0 && interpret)
		return (*s = 1, REDIR_IN);
	if (ft_strncmp(str, ">>", len) == 0 && interpret)
		return (*s = 1, REDIR_OUT);
	if (*s == 1)
		return (*s = 0, FILE);
	if (*t == 0)
		return (*t = 1, CMD);
	if (*t == 1)
		return (ARG);
	return (0);
}

t_line	*subsplit(char *str, int l[2], int *j, t_shell *shell)
{
	t_line	*new;
	t_line	*current;
	int		i;
	char	**subsplit;

	subsplit = another_split(str, ' ', shell);
	if (!subsplit)
		return (NULL);
	new = NULL;
	i = 0;
	while (subsplit[i])
	{
		current
			= line_new(subsplit[i], check_type(subsplit[i], &l[0], &l[1], 0), (*j)++);
		if (!current)
			return (free_arr(subsplit, ft_countwords(str, ' ')), NULL);
		line_add_back(&new, &current);
		i++;
	}
	free_arr(subsplit, ft_countwords(str, ' '));
	return (new);
}
