/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:01:38 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 17:53:22 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	set_ignore(int *ignore, char c)
{
	if (is_quote(c) && !(*ignore))
		*ignore = 1;
	else if (is_quote(c) && *ignore)
		*ignore = 0;
}

static char	*custom_cpytillsep(char const *s, char c, int ignore)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	if (is_sep(s))
		len += is_sep(s);
	else
		while (s[len] && ((s[len] != c && !is_sep(s + len)) || ignore))
			set_ignore(&ignore, s[len++]);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && (s[i] != c || ignore))
	{
		str[i] = s[i];
		set_ignore(&ignore, s[i++]);
	}
	str[i] = '\0';
	return (str);
}

int  custom_countwords(char *str, char sep)
{
	int count;
	int i;
	int words;

	count = 1;
	i = -1;
	words = 0;
	while (str[++i])
	{
		if (is_sep(str + i) || (count == 1 && str[i] != sep))
		{
			words++;
			count = 0;
		}
		if ((count == 0 && str[i] == sep) || is_sep(str + i))
			count = 1;
		if (is_quote(str[i]))
			while (str[++i] && !is_quote(str[i]))
				i = i + 0;
	}
	return (words);
}

static char	**ft_alloc(char const *s, char c, char **split)
{
	int		i;
	int		j;
	int		ignore;

	i = 0;
	j = 0;
	ignore = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j++] = custom_cpytillsep(s + i, c, 0);
			if (!split[j - 1])
				return (free_arr(split, j), NULL);
			if (is_sep(s + i))
				i += is_sep(s + i);
			else
				while (s[i] && ((s[i] != c && !is_sep(s + i)) || ignore))
					set_ignore(&ignore, s[i++]);
		}
		else
			i++;
	}
	split[j] = 0;
	return (split);
}

char	**custom_split(char *str, char sep)
{
	char	**split;

	split = malloc(sizeof(char *) * (custom_countwords(str, sep) + 1));
	if (!split)
		return (NULL);
	split = ft_alloc(str, sep, split);
	if (!split)
		return (NULL);
	return (split);
}
