/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:04:28 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/07 15:45:39 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbdigits(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int c)
{
	long	n;
	int		i;
	char	*str;

	n = c;
	i = ft_nbdigits(n);
	str = ft_calloc(sizeof(char), (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[i--] = '\0';
	while (i >= 0 && str[i] != '-')
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
