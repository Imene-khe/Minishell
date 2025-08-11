#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
extern int  g_signal;
void        setup_signals_interactive(void);
void	setup_signals_child(void);
int		interpret_wait_status(int wstatus);


#endif
