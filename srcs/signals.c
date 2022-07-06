#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    if (!kill(g_pid, signo))
    {
        if (signo == SIGQUIT)
            printf("Quit\n");
        else if (signo == SIGINT)
            printf("\n");
    }
	else if (signo == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}