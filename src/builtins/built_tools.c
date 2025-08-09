/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:54:07 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 16:22:47 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_verify(t_tree *args)
{
	if (count_elm(args, ARG) == 0 || (count_elm(args, ARG) == 1
			&& !ft_strcmp(args->content, "~")))
		return (1);
	return (0);
}
