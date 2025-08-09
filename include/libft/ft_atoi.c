/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:23 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/07 16:30:29 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned char	*p;
	int				n;
	int				i;
	int				s;

	p = (unsigned char *) nptr;
	i = 0;
	n = 0;
	s = 1;
	while (ft_isspace(p[i]))
		i++;
	if (p[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (p[i] == '+')
		i++;
	while (ft_isdigit(p[i]))
		n = 10 * n + (p[i++] - '0');
	return (n * s);
}

long long	ft_atoll(const char *nptr)
{
	unsigned char	*p;
	long long		n;
	long long		i;
	long long		s;

	p = (unsigned char *) nptr;
	i = 0;
	n = 0;
	s = 1;
	while (ft_isspace(p[i]))
		i++;
	if (p[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (p[i] == '+')
		i++;
	while (ft_isdigit(p[i]))
		n = 10 * n + (p[i++] - '0');
	return (n * s);
}
