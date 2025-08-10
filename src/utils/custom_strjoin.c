/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:44:40 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 17:46:02 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	len_val(char *s1, char *s2, char *str, t_shell *shell);

char	*custom_strjoin(char *s1, char *s2, char *str, t_shell *shell)
{
	int		len;
	int		j;
	char	*join;
	char	*tmp;

	if (!s2)
		return (s1);
	len = len_val(s1, s2, str, shell);
	if (len < 0)
		return (free(s1), NULL);
	join = ft_strndup(s1, len);
	if (!join)
		return (free(s1), NULL);
	j = ft_strlen(s1);
	if (!ft_strcmp(s2, "?"))
	{
		tmp = ft_itoa(shell->status);
		if (!tmp)
			return (free(s1), free(join), NULL);
		ft_strlcpy(join + j, tmp, len + 1);
		free(tmp);
	}
	else
		ft_strlcpy(join + j, ft_getenv(shell->envp, s2), len);
	return (free(s1), join);
}

int	len_val(char *s1, char *s2, char *str, t_shell *shell)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	if (!ft_strcmp(s2, "?"))
	{
		tmp = ft_itoa(shell->status);
		if (!tmp)
			return (-1);
		ret = ft_strlen(s1) + ft_strlen(str) - ft_strlen(s2) + ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		ret = ft_strlen(s1) + ft_strlen(str) - ft_strlen(s2)
			+ ft_strlen(ft_getenv(shell->envp, s2));
	}
	return (ret);
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
