/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:18:50 by bguerrou          #+#    #+#             */
/*   Updated: 2025/01/29 11:50:52 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isconversion(const char *str)
{
	if (str[0] == '%' && (str[1] == 'c' || str[1] == 's' || str[1] == 'p'
			|| str[1] == 'd' || str[1] == 'i' || str[1] == 'u' || str[1] == 'x'
			|| str[1] == 'X' || str[1] == '%'))
		return (1);
	return (0);
}

static void	ft_print(const char *str, va_list args, int i, int *charcount)
{
	if (str[i + 1] == 'c')
		ft_putchar_counts(va_arg(args, int), charcount);
	else if (str[i + 1] == 's')
		ft_putstr_counts(va_arg(args, char *), charcount);
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		ft_putnbr_counts(va_arg(args, int), charcount);
	else if (str[i + 1] == 'u')
		ft_putnbrbase_counts(va_arg(args, unsigned int), "0123456789",
			charcount, 0);
	else if (str[i + 1] == 'x')
		ft_putnbrbase_counts(va_arg(args, unsigned int),
			"0123456789abcdef", charcount, 1);
	else if (str[i + 1] == 'X')
		ft_putnbrbase_counts(va_arg(args, unsigned int),
			"0123456789ABCDEF", charcount, 1);
	else if (str[i + 1] == 'p')
		ft_putnbrbase_counts(va_arg(args, uintptr_t),
			"0123456789abcdef", charcount, 0);
	else if (str[i + 1] == '%')
		ft_putchar_counts('%', charcount);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		charcount;

	i = 0;
	charcount = 0;
	va_start(args, str);
	while (str[i])
	{
		while (str[i] && !ft_isconversion(str + i))
			ft_putchar_counts(str[i++], &charcount);
		if (str[i])
		{
			ft_print(str, args, i, &charcount);
			i += 2;
		}
	}
	va_end(args);
	return (charcount);
}
