#include "../include/minishell.h"

void    signal_handler_process(int signo)
{
    if (signo == SIGINT)
        printf("\n");
    else
    {
        printf("Quit: %d\n", signo);
    }
}

void	signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}