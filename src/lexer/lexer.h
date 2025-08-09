/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:15:58 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 13:19:34 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../include/minishell.h"
# include "../utils/utils.h"
# include "../utils/lists/lists.h"
# include "../expander/expander.h"

struct s_line  *lexer(char *prompt, t_shell *shell);

#endif