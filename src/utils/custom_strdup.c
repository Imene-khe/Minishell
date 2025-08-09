/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:46:54 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/09 16:52:34 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	check_quotes(char c, int *ignore, int *type)
{
	if (*ignore == 0 && is_quote(c))
	{
		*ignore = 1;
		*type = is_quote(c);
		return (0);
	}
	if (*ignore == 1 && *type == is_quote(c))
	{
		*ignore = 0;
		*type = 0;
		return (0);
	}
	return (1);
}

char	*custom_strdup(const char *s)
{
	size_t		slen;
	char		*dup;
	size_t		i;
	size_t		j;
	int			ignore;
	int			type;

	slen = ft_strlen(s);
	dup = ft_calloc(sizeof(char), slen + 1);
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	ignore = 0;
	type = 0;
	while (i < slen)
	{
		if (check_quotes(s[i], &ignore, &type))
			dup[j++] = s[i];
		i++;
	}
	return (dup);
}
