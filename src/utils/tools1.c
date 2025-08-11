/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:39:04 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 17:22:19 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	nothing(char *str)
{
	int		i;
	int		char_nb;
	char	c;
	i = 0;
	char_nb = 0;
	c = 0;
	while (str[i] && char_nb <= 1)
	{
		if (str[i++] != ' ')
		{
			char_nb++;
			c = str[i - 1];
		}
	}
	if (char_nb > 1)
		return (0);
	if (c == '!' || c == ':')
		return (1);
	return (0);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (nothing(str));
	return (1);
}

static void ignore_quote(char *s, int *i, int which, int *count)
{
	*count = -*count;
	*i += 1;
	while (s[*i] && is_quote(s[*i]) != which)
		(*i)++;
	if (s[*i])
	{
		*count = -*count;
		*i += 1;
	}
}

int	closed(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 1;
	double_quote = 1;
	while (str[i])
	{
		if (is_quote(str[i]) == 1)
			ignore_quote(str, &i, 1, &single_quote);
		if (str[i] && is_quote(str[i]) == 2)
			ignore_quote(str, &i, 2, &double_quote);
		if (str[i] && is_quote(str[i]) == 0)
			i++;
	}
	if (single_quote < 0 || double_quote < 0)
		return (printf("Please close your quotes.\n"), 0);
	return (1);
}

int	is_sep(const char *str)
{
	if (str[0] != '|' && str[0] != '<' && str[0] != '>'
			&& ft_strncmp(str, "<<", 2) != 0
			&& ft_strncmp(str, ">>", 2) != 0)
		return (0);
	if (!ft_strncmp(str, "<<", 2)
			|| !ft_strncmp(str, ">>", 2))
		return (2);
	return (1);
}
