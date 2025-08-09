/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi2020@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:47:05 by bguerrou          #+#    #+#             */
/*   Updated: 2024/11/18 17:50:23 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	if (s[slen] == (char) c)
		return ((char *) &s[slen]);
	while (slen-- > 0)
	{
		if (s[slen] == (char) c)
			return ((char *) &s[slen]);
	}
	return (0);
}
