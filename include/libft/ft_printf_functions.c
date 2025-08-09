/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:55:04 by bguerrou          #+#    #+#             */
/*   Updated: 2025/01/29 11:50:44 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_counts(char c, int *charcount)
{
	write(1, &c, 1);
	(*charcount)++;
}

void	ft_putstr_counts(char *s, int *charcount)
{
	int	i;

	i = 0;
	if (!s)
		ft_putstr_counts("(null)", charcount);
	else
	{
		while (s[i])
			ft_putchar_counts(s[i++], charcount);
	}
}

void	ft_putnbr_counts(int n, int *charcount)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_counts('-', charcount);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_counts(nb / 10, charcount);
	ft_putchar_counts((char)(nb % 10 + '0'), charcount);
}

void	ft_putnbrbase_counts(uintptr_t n, char *base, int *charcount, int iter)
{
	uintptr_t	nb;
	uintptr_t	len;

	len = ft_strlen(base);
	if (n == 0 && iter == 0 && len == 16)
		ft_putstr_counts("(nil)", charcount);
	else
	{
		if (iter == 0 && len == 16)
			ft_putstr_counts("0x", charcount);
		nb = n;
		if (nb >= len)
		{
			ft_putnbrbase_counts(nb / len, base, charcount, iter + 1);
			ft_putnbrbase_counts(nb % len, base, charcount, iter + 1);
		}
		else
			ft_putchar_counts(base[nb], charcount);
	}
}
