/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi2020@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:07:25 by bguerrou          #+#    #+#             */
/*   Updated: 2024/11/18 17:51:30 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t				i;
	size_t				littlelen;

	littlelen = ft_strlen(little);
	if (littlelen == 0)
		return ((char *)big);
	i = 0;
	while (i < len && big[i] && littlelen <= len - i)
	{
		if (ft_strncmp(big + i, little, littlelen) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
