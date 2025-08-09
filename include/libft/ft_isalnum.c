/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:24:53 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 14:13:00 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

int	ft_isallalnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i])
		return (0);
	return (1);
}
