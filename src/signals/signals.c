#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>

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
	signal(SIGINT, sigint_interactive);
	signal(SIGQUIT, ignore_handler);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	interpret_wait_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
	{
		int	sig = WTERMSIG(wstatus);

		if (sig == SIGQUIT)
			write(2, "Quit\n", 5);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		return (128 + sig);
        // pour le recup et savoir on arrete notre truc avec quelle manip
	}
	return (0);
}

