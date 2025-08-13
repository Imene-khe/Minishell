/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:15:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/13 16:41:24 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_line	*lexer_next(char **split, int *t, int *s, t_shell *shell);
int		check_type(char *str, int *t, int *s, int interpret);
t_line	*subsplit(char *str, int *t, int *s, int *j);

t_line	*lexer(char *prompt, t_shell *shell)
{
	t_line	*head;
	char	**split;
	int		t;
	int		s;

	split = custom_split(prompt, ' ');
	if (!split)
		return (NULL);
	t = 0;
	s = 0;
	head = lexer_next(split, &t, &s, shell);
	free_arr(split, custom_countwords(prompt, ' '));
	if (!head)
		return (NULL);
	return (head);
}

t_line	*lexer_next(char **split, int *t, int *s, t_shell *shell)
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
		expanded = expand(split[i], shell, 0);
		if (!expanded)
			return (line_free(head), NULL);
		if (ft_countwords(expanded, ' ') <= 1 || *s)
			current = line_new(expanded, check_type(expanded, t, s, 1), j++);
		else
			current = subsplit(expanded, t, s, &j);
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

t_line	*subsplit(char *str, int *t, int *s, int *j)
{
	t_line	*new;
	t_line	*current;
	int		i;
	char	**subsplit;

	subsplit = custom_split(str, ' ');
	if (!subsplit)
		return (NULL);
	new = NULL;
	i = 0;
	while (subsplit[i])
	{
		current
			= line_new(subsplit[i], check_type(subsplit[i], t, s, 0), (*j)++);
		if (!current)
			return (free_arr(subsplit, ft_countwords(str, ' ')), NULL);
		line_add_back(&new, &current);
		i++;
	}
	free_arr(subsplit, ft_countwords(str, ' '));
	return (new);
}
