/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/07 17:25:12 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*replacing(char *expanded, char *str, int *i, t_shell *shell)
{
	char	*var;
	char	*tmp;

	tmp = NULL;
	var = var_name(str + *i);
	if (!var)
		return (free(expanded), NULL);
	if (ft_strcmp(var, "?") == 0)
	{
		tmp = ft_itoa(shell->status);
		expanded = custom_strjoin(expanded, tmp, str + *i, shell);
		free(tmp);
	}
	else
		expanded = custom_strjoin(expanded, var, str + *i, shell);
	*i += ft_strlen(var) + 1;
	free(var);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*expand(char *str, t_shell *shell)
{
	char	*expanded;
	int		i;
	int		j;
	int		mode;

	expanded = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	mode = 0;
	while (str[i])
	{
		if (!change_mode(str[i], &mode) && str[i] == '$' && till_sep(str + i + 1) && mode != 1)
		{
			expanded = replacing(expanded, str, &i, shell);
			if (!expanded)
				return (NULL);
			while (expanded[j])
				j++;
		}
		else
			expanded[j++] = str[i++];
	}
	return (expanded);
}
