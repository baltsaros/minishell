#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void	*context)
{
    (void)signo;
    (void)info;
    (void)context;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}