/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/10 20:12:33 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "signals/signals.h"

pid_t	g_signal_pid;

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
int next(t_shell *shell)
{
    int   run;
    char *prompt;

    setup_signals_interactive();
    run = 1;
    while (run)
    {
        prompt = readline("minishishishi > ");
        if (!prompt)
		{
            write(1, "exit\n", 5);
            break;
        }
        if (only_spaces(prompt) || ft_strlen(prompt) == 0) {
            free(prompt);
            continue;
        }
        treatment(prompt, &run, shell);
    }
    return (shell->status);
}
/*int	next(t_shell *shell)
{
	int	run;
	char	*prompt;

	run = 1; // win nzid 9samha
	while (run)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
			return (print_error("Malloc failed", "readline"), 1);
		if (!only_spaces(prompt) && ft_strlen(prompt) > 0)
			treatment(prompt, &run, shell);
	}
	
	return (shell->status);
}*/
/*int	next(t_shell *shell)
{
	int	run;
	setup_signals_interactive();
	char	*prompt;

	run = 1;
	while (run)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
			return (print_error("Malloc failed", "readline"), 1); ca je l'enelve
			car en gros maintenant je prends en consideration control + D
		if (!prompt)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (!only_spaces(prompt) || ft_strlen(prompt) == 0)
		{
			free(prompt);
			continue;
		}
		treatment(prompt, &run, shell);
	}
	return (shell->status);
}*/
