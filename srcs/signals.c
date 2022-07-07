#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void *context)
{
    // Ctrl + C
	if (signo == SIGINT)
    {
        printf("SIGINT\n");
    }
    // Ctrl + '\'
	else if (signo == SIGQUIT)
    {
        printf("SIGQUIT\n");
    }
		
	(void)signo;
	(void)info;
	(void)context;
}