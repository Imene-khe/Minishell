/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:35:55 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/16 00:25:07 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../include/minishell.h"

// Split
int		custom_countwords(char *str, char sep);
char	**custom_split(char *str, char sep);

// Split Again
char	**another_split(char *str, char sep, t_shell *shell);

// Tools 1
int		only_spaces(char *str, int step);
int		closed(char *str);
int		is_sep(const char *str);

// Tools 2
int		is_quote(char c);
int		arr_size(char **arr);
char	**ft_arrdup(char **arr, int size);
int		is_dir(const char *cmd);
void	set_ignore(int *ignore, char c);

// Tools 3
int		until_sep(char *str, char sep);
char	**cmnd_split(char *path, t_tree *args, t_exec *ex);
void	modify_var(t_exec *ex, char *name, char *value, char *other);
int		too_big(char *str, int size);
void	env_process(t_exec *ex, t_tree *args, int count, int *run);

// Custom Strdup
int		count_quote(const char *s, int type);
char	*custom_strdup(const char *s, int ignore, int type);

// Custom strjoin
char	*custom_strjoin(char *s1, char *s2, char *str, t_shell *shell);
char	*new_strjoin(char *s1, char *s2);

// Frees
void	free_structs(t_tree *tree, t_exec *ex, int s);
void	free_shell(t_shell *shell);
void	free_exec(t_exec *exec);
void	close_fds(int *fds);

#endif