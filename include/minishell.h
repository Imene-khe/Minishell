/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:20 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/14 14:37:41 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

# include "luffy.h"
# include "structs.h"
# include "../src/lexer/lexer.h"
# include "../src/expander/expander.h"
# include "../src/utils/lists/lists.h"
# include "../src/environment/env.h"
# include "../src/parser/parser.h"
# include "../src/utils/trees/trees.h"
# include "../src/executor/exec.h"
# include "../src/builtins/builtins.h"
# include "../src/errors/errors.h"
# include "../src/utils/utils.h"
# include "../src/signals/signals.h"

# define CMD 1
# define ARG 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define PIPE 5
# define FILE 6
# define EMPTY 7

# define PATH_SIZE 5000

void	treatment(char *prompt, int *run, t_shell *shell);

#endif