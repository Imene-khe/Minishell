/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:00:08 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/23 17:06:59 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../include/minishell.h"

// ENV 1
t_env	*env_new(char *var);
void	env_add_back(t_env **head, t_env *new);
void	env_free(t_env *head);
t_env	*env_find(t_env *head, char *name);
int		env_size(t_env *env);

// ENV 2
void	env_delete(t_env *head, t_env *target);
t_env	*arr_to_env(char **envp);
char	**env_to_arr(t_env *env);
char	*ft_getenv(t_env *env, char *name);

// ENV 3
t_env	*env_dup(t_env *env);

#endif