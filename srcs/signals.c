#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void	*context)
{
	int	status;
	int	status_wait;

	(void)info;
	(void)context;
	status_wait = waitpid(-1, &status, WNOHANG);
	if (status_wait == -1)
	{
		if (signo == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
	{
		if (signo == SIGINT)
		{
			write(1, "\n", 1);
			kill(g_pid, signo);
		}
		else
		{
			write(1, "Quit\n", 5);
			kill(g_pid, signo);
		}
	}
}
