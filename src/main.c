/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/17 14:49:02 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "signals/signals.h"

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
	shell->history = NULL;
	//printf("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	exit_code = next(shell);
	free_shell(shell);
	return (exit_code);
}

int	next(t_shell *shell)
{
	int		run;
	char	*prompt;

	prompt = NULL;
	setup_signals_interactive();
	run = 1;
	while (run)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
			exit_built(NULL, NULL, &run);
		if (run && !only_spaces(prompt, 1) && ft_strlen(prompt) > 0)
			treatment(prompt, &run, shell);
	}
	return (shell->status);
}
