/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:10:24 by bguerrou          #+#    #+#             */
/*   Updated: 2025/01/29 11:56:31 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_repet(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j++])
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_putnbrbase_fd(unsigned int n, char *base, int fd)
{
	unsigned long	nb;
	unsigned int	len;

	len = ft_strlen(base);
	nb = n;
	if (len <= 1 || ft_repet(base))
		return ;
	if (nb >= len)
	{
		ft_putnbrbase_fd(nb / len, base, fd);
		ft_putnbrbase_fd(nb % len, base, fd);
	}
	else
		ft_putchar_fd((char)(base[nb]), fd);
}
