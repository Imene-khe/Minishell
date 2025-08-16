/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 11:04:02 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int		expand_verify(char *str, int *i, int *mode);
char	*replacing(char *expanded, char *str, int *i, t_shell *shell);
int		is_quoted(char *s, int i, int type, t_shell *shell);

char	*expand(char *str, t_shell *shell, int mode)
{
	char	*expanded;
	int		i;
	int		j;

	expanded = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (expand_verify(str, &i, &mode))
		{
			is_quoted(str, i, 2, shell);
			expanded = replacing(expanded, str, &i, shell);
			if (!expanded)
				return (NULL);
			while (expanded[j])
				j++;
		}
		else
			expanded[j++] = str[i++];
	}
	return (expanded);
}

char	*replacing(char *expanded, char *str, int *i, t_shell *shell)
{
	char	*var;

	var = var_name(str + *i);
	if (!var)
		return (free(expanded), NULL);
	expanded = custom_strjoin(expanded, var, str + *i, shell);
	*i += ft_strlen(var) + 1;
	free(var);
	return (expanded);
}

int	expand_verify(char *str, int *i, int *mode)
{
	if (!change_mode(str[*i], mode) && str[*i] == '$')
	{
		if (str[*i + 1] && is_quote(str[*i + 1]) && *mode == 0)
		{
			(*i)++;
			return (0);
		}
		if (till_sep(str + *i + 1) && *mode != 1)
			return (1);
	}
	return (0);
}

int	is_quoted(char *s, int i, int type, t_shell *shell)
{
	int		j;

	j = -1;
	while (s[++j])
	{
		if (is_quote(s[j]) == type)
		{
			while (s[j] && (is_quote(s[j]) != type || is_quote(s[j]) == 0))
				j++;
			if (s[j] && j < i)
				j++;
			else if (s[j])
				return (shell->quoted = 1, 1);
		}
	}
	return (0);
}
