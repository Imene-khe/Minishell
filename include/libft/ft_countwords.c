/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:01:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/02/25 13:05:23 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char const *s, char c)
{
	int	count;
	int	i;
	int	words;

	count = 1;
	i = 0;
	words = 0;
	while (s[i])
	{
		if (count == 1 && s[i] != c)
		{
			words++;
			count = 0;
		}
		else if (count == 0 && s[i] == c)
			count = 1;
		i++;
	}
	return (words);
}
