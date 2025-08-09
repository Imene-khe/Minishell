/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:44:40 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/02 17:50:23 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*custom_strjoin(char *s1, char *s2, char *str, t_shell *shell)
{
	size_t	len;
	size_t	j;
	char	*join;

	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(str) - ft_strlen(s2)
		+ ft_strlen(ft_getenv(shell->envp, s2));
	join = ft_calloc(sizeof(char), len + 1);
	if (!join)
		return (free(s1), NULL);
	j = -1;
	while (s1[++j])
		join[j] = (s1)[j];
	free(s1);
	ft_strlcpy(join + j, ft_getenv(shell->envp, s2), len);
	return (join);
}

char	*new_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*join;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_calloc(sizeof(char), len + 2);
	if (!join)
		return (free(s1), NULL);
	ft_strlcpy(join, s1, len + 1);
	free(s1);
	ft_strlcat(join, s2, len + 1);
	return (join);
}
