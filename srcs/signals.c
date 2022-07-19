#include "../include/minishell.h"

void	signal_handling(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_fork(int signo)
{
	kill(-2, signo);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	signal_hd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	g_status = 130;
	exit(g_status);
}