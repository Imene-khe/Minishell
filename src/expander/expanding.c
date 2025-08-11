/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:12:51 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 17:04:24 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*replacing(char *expanded, char *str, int *i, t_shell *shell)
{
	char	*var;

	var = var_name(str + *i);
	if (!var)
		return (free(expanded), NULL);
	expanded = custom_strjoin(expanded, var, str + *i, shell);
	*i += ft_strlen(var) + 1;
	free(var);
	return (expanded);
}

char	*expand(char *str, t_shell *shell, int mode)
{
	char	*expanded;
	int		i;
	int		j;

	expanded = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
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
