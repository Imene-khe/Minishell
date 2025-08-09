/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi2020@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:03:36 by bguerrou          #+#    #+#             */
/*   Updated: 2024/11/18 18:04:12 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alterstrndup(const char *s, size_t n)
{
	char		*dup;
	size_t		i;
	size_t		slen;

	slen = ft_strlen(s);
	if (slen >= n)
		dup = malloc(sizeof(char) * n + 1);
	else
		dup = malloc(sizeof(char) * slen + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;

	if (start >= ft_strlen(s))
		sub = ft_alterstrndup("", len);
	else
		sub = ft_alterstrndup(&s[start], len);
	if (!sub)
		return (NULL);
	return (sub);
}
