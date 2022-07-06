#include "../include/minishell.h"

int check_next_and_type(t_node  *args)
{
    if (!args->next)
    {
        write(1, "[ERROR]: syntax error near unexpected token `", 45);
        write(1, "newline", 7);
        write(1, "'\n", 2);
        return (1);
    }
    else if (args->next->type != WORD)
    {
        write(1, "[ERROR]: syntax error near unexpected token `", 45);
        write(1, args->next->value, ft_strlen(args->value));
        write(1, "'\n", 2);
        return (1);
    }
    return (0);
}

int syntax_checker(t_node *args)
{
    while (args)
    {
        if (args->type == REDIR_OUT || args->type == REDIR_IN
            || args->type == REDIR_AP || args->type == REDIR_HD)
        {
            if (check_next_and_type(args) == 1)
                return (1);
        }
        args = args->next;
    }
    return (0);
}