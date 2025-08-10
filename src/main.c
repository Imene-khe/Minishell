/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/09 17:53:26 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	next(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void) argc;
	(void) argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (print_error("Malloc failed", "shell"), exit(1), 1);
	shell->envp = arr_to_env(envp);
	shell->status = 0;
	printf("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	exit_code = next(shell);
	free_shell(shell);
	return (exit_code);
}

int	next(t_shell *shell)
{
	int		run;
	char	*prompt;

	run = 1;
	while (run)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
			return (print_error("Malloc failed", "readline"), 1);
		if (!only_spaces(prompt) && ft_strlen(prompt) > 0)
			treatment(prompt, &run, shell);
	}
	return (shell->status);
}
