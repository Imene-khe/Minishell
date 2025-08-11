/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:44:40 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 18:24:29 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*next_strjoin(char *s1, char *s2, int len, t_shell *shell);
char	*cut_spaces(char *str);
int		len_val(char *s1, char *s2, char *str, t_shell *shell);

char	*custom_strjoin(char *s1, char *s2, char *str, t_shell *shell)
{
	int		len;
	char	*join;

	if (!s2)
		return (s1);
	len = len_val(s1, s2, str, shell);
	if (len < 0)
		return (free(s1), NULL);
	join = next_strjoin(s1, s2, len, shell);
	return (join);
}

char	*next_strjoin(char *s1, char *s2, int len, t_shell *shell)
{
	char	*tmp;
	int		j;
	char	*join;

	join = ft_strndup(s1, len);
	if (!join)
		return (free(s1), NULL);
	j = ft_strlen(s1);
	if (!ft_strcmp(s2, "?"))
	{
		tmp = ft_itoa(shell->status);
		if (!tmp)
			return (free(s1), free(join), NULL);
	}
	else
	{
		tmp = cut_spaces(ft_getenv(shell->envp, s2));
		if (!tmp)
			return (free(s1), free(join), NULL);
	}
	ft_strlcpy(join + j, tmp, len + 1);
	return (free(s1), free(tmp), join);
}

char	*cut_spaces(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			while (str[i] && str[i] == ' ')
				i++;
		else
		{
			while (str[i] && str[i] != ' ')
				new[j++] = str[i++];
			if (str[i] && !only_spaces(str + i))
				new[j++] = ' ';
		}
	}
	new[j] = '\0';
	return (new);
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
