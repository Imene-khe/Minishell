/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi2020@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:04:24 by bguerrou          #+#    #+#             */
/*   Updated: 2024/11/18 17:41:06 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_instr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_countlen(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (ft_instr(set, s1[len]))
		len++;
	if (len == ft_strlen(s1))
		return (0);
	i = ft_strlen(s1) - 1;
	while (ft_instr(set, s1[i--]))
		len++;
	len = ft_strlen(s1) - len;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_countlen(s1, set);
	trim = malloc(sizeof(char) * len + 1);
	if (!trim)
		return (NULL);
	i = 0;
	while (ft_instr(set, s1[i]))
		i++;
	j = 0;
	while (j < len && s1[i])
		trim[j++] = s1[i++];
	trim[j] = '\0';
	return (trim);
}
