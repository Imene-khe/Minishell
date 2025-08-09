/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi2020@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:19:22 by bguerrou          #+#    #+#             */
/*   Updated: 2024/11/18 17:33:37 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dtmp;
	unsigned char	*stmp;
	size_t			i;

	if (!dest && !src)
		return (dest);
	dtmp = (unsigned char *) dest;
	stmp = (unsigned char *) src;
	i = 0;
	if (dtmp > stmp)
	{
		while (n-- > 0)
			dtmp[n] = stmp[n];
	}
	else
	{
		while (i < n)
		{
			dtmp[i] = stmp[i];
			i++;
		}
	}
	return (dest);
}
