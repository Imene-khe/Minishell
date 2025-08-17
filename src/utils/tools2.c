/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:54:08 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/17 23:26:31 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	arr_size(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

char	**ft_arrdup(char **arr, int size)
{
	char	**dup;
	int		i;

	if (!arr)
		return (NULL);
	dup = ft_calloc(sizeof(char *), size + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i] && i < size)
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (free_arr(dup, i), NULL);
		i++;
	}
	return (dup);
}

int	is_dir(const char *cmd)
{
	int	i;
	int	slash;
	int	dot;

	i = -1;
	slash = 0;
	dot = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
			slash++;
		if (cmd[i] == '.')
			dot++;
	}
	if ((slash == i || (dot == 1 && i == 1)
			|| slash + dot == i) && i > 0)
		return (1);
	return (0);
}

void	set_ignore(int *ignore, char c)
{
	if (is_quote(c) && !(*ignore))
		*ignore = is_quote(c);
	else if (*ignore && *ignore == is_quote(c))
		*ignore = 0;
}
