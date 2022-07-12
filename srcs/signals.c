#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void	*context)
{
	(void)info;
	(void)context;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
