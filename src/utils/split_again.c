/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:18:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 00:29:31 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	**another_alloc(char const *s, char c, char **split, t_shell *shell);
static char	*another_cpytillsep(char const *s, char c, int ignore, t_shell *shell);

char	**another_split(char *str, char sep, t_shell *shell)
{
	char	**split;

	split = ft_calloc(sizeof(char *), (custom_countwords(str, sep) + 1));
	if (!split)
		return (NULL);
	split = another_alloc(str, sep, split, shell);
	if (!split)
		return (NULL);
	return (split);
}

static char	**another_alloc(char const *s, char c, char **split, t_shell *shell)
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
			split[j++] = another_cpytillsep(s + i, c, 0, shell);
			if (!split[j - 1])
				return (free_arr(split, j), NULL);
			if (is_sep(s + i))
				i += is_sep(s + i);
			else
				while (s[i] && ((s[i] != c && !is_sep(s + i)) || ignore || shell->quoted))
					set_ignore(&ignore, s[i++]);
		}
		else
			i++;
	}
	split[j] = 0;
	return (split);
}

static char	*another_cpytillsep(char const *s, char c, int ignore, t_shell *shell)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	if (is_sep(s))
		len += is_sep(s);
	else
		while (s[len] && ((s[len] != c && !is_sep(s + len)) || ignore || shell->quoted))
			set_ignore(&ignore, s[len++]);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		set_ignore(&ignore, s[i++]);
	}
	str[i] = '\0';
	return (str);
}
