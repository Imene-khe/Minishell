/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:14 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/07 14:30:33 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	if (!nmemb || !size)
		return (NULL);
	mem = malloc(nmemb * (size + 1));
	if (!mem)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		mem[i++] = 0;
	return (mem);
}

void	*custom_calloc(size_t nmemb, size_t size, int val)
{
	unsigned char	*mem;
	size_t			i;

	if (!nmemb || !size)
		return (NULL);
	mem = malloc(nmemb * (size + 1));
	if (!mem)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		mem[i++] = val;
	return (mem);
}
