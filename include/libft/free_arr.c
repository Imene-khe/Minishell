/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:06:11 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/22 12:16:44 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_arr(char **arr, int size)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size && arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}
