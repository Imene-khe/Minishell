#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

int	g_signal = 0;

static void	sigint_interactive(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ignore_handler(int signo)
{
	(void)signo;
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_interactive;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ignore_handler;
	sigaction(SIGQUIT, &sa, NULL);
}
