/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:35:55 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/11 15:34:08 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

# include "../../include/minishell.h"

// Split
int		custom_countwords(char *str, char sep);
char	**custom_split(char *str, char sep);

// Tools 1
int		only_spaces(char *str);
int		closed(char *str);
int		is_sep(const char *str);

// Tools 2
int		is_quote(char c);
int		arr_size(char **arr);
char	**ft_arrdup(char **arr, int size);
int	    is_dir(const char *cmd);

// Tools 3
int		until_sep(char *str, char sep);
char	**cmnd_split(char *path, t_tree *args, t_exec *ex);
void	modify_var(t_exec *ex, char *name, char *value, char *other);
int 	too_big(char *str, int size);

// Custom Strdup
char	*custom_strdup(const char *s);

// Custom strjoin
char	*custom_strjoin(char *s1, char *s2, char *str, t_shell *shell);
char	*new_strjoin(char *s1, char *s2);

// Frees
void	free_structs(t_tree *tree, t_exec *ex, int s);
void	free_shell(t_shell *shell);
void	free_exec(t_exec *exec);
void    close_fds(int *fds);

#endif