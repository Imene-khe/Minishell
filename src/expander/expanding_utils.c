/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:17:18 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/01 14:17:11 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	till_sep(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$'
			&& str[i] != '\'' && str[i] != '\"' && str[i] != '='
			&& str[i] != '\\' && str[i] != '/')
		i++;
	return (i);
}

int	change_mode(char c, int *mode)
{
	if (c == '\'' && *mode == 0)
		*mode = 1;
	else if (c == '\"' && *mode == 0)
		*mode = 2;
	else if ((c == '\'' && *mode == 1) || (c == '\"' && *mode == 2))
		*mode = 0;
	else
		return (0);
	return (1);
}

char	*var_name(char *str)
{
	char	*name;

	name = ft_strndup(str + 1, till_sep(str + 1));
	if (!name)
		return (NULL);
	return (name);
}

int	splittable(char *str, char c)
{
	int	words;
	int	i;
	int	count;

	words = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (count == 0 && str[i] != c)
		{
			count = 1;
			words++;
		}
		else if (count == 1 && str[i] == c)
			count = 0;
		i++;
	}
	return (words);
}
