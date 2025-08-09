/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:15:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/08 19:46:48 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_line
{
	char			*content;
	int				type;
	int				nb;
	struct s_line	*next;
}					t_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tree
{
	char			*content;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_shell
{
	t_env			*envp;
	int				status;
}					t_shell;

typedef struct s_exec
{
	t_tree	*tree;
	t_shell	*shell;
	char	**paths;
	int		read_fd;
	int		write_fd;
	int		*pid;
	int		in_env;
	int		pipe1[2];
	int		pipe2[2];
	int		need_pipe;
	int		need_fork;
	int		cmd_count;
	int		in_redirs;
	int		out_redirs;
}			t_exec;

#endif