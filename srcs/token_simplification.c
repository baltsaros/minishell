#include "../include/minishell.h"

void    dollar_management(t_node    *elem, t_input  *data)
{
    elem = dollar_token_simplification(elem, data);
    if (elem->type == ENV_VA)
        elem->value = ms_strdup(getenv(elem->value + 1), data);
    else if (elem->type == ENV_VA_BR)
        elem->value = ms_strdup(getenv(get_between_braces(elem, BRACES_L, BRACES_R)), data);
    else if (elem->type == ENV_P)
        elem->value = ms_strdup(get_between_braces(elem, BR_L, BR_R), data);
    else if (elem->type == ENV_P_EM)
    {
        elem->type = 0;
        free(elem->value);
        elem->value = ms_strdup(NULL, data);
    }  
}

void    out_arg_management(t_node    *elem)
{
    if (elem->next && (elem->next && elem->next->type == WSPACE))
    {
        elem = elem->next;
        if (elem->next && (elem->next->type != PIPE && elem->next->type != REDIR_IN && elem->next->type != REDIR_OUT 
            && elem->next->type != REDIR_HD && elem->next->type != REDIR_AP))
            elem->next->type = OUT_ARG;
    }
    else if (elem->next && (elem->next->type != PIPE && elem->next->type != REDIR_IN && elem->next->type != REDIR_OUT 
        && elem->next->type != REDIR_HD && elem->next->type != REDIR_AP))
        elem->next->type = OUT_ARG;
}

void    in_arg_management(t_node    *elem)
{
    if (elem->next && (elem->next && elem->next->type == WSPACE))
    {
        elem = elem->next;
        if (elem->next && (elem->next->type != PIPE && elem->next->type != REDIR_IN && elem->next->type != REDIR_OUT 
            && elem->next->type != REDIR_HD && elem->next->type != REDIR_AP))
            elem->next->type = IN_ARG;
    }
    else if (elem->next && (elem->next->type != PIPE && elem->next->type != REDIR_IN && elem->next->type != REDIR_OUT 
        && elem->next->type != REDIR_HD && elem->next->type != REDIR_AP))
        elem->next->type = IN_ARG;
}

int general_simplification(t_node   *elem, t_input  *data)
{
    while (elem)
    {
        if (elem->type == DOLLAR)
            dollar_management(elem, data);
        else if (elem->type == WORD && !ft_strncmp(elem->value, ".", 2))
            elem = executable_token_simplification(elem, data);
        else if (elem->type == REDIR_OUT || elem->type == REDIR_AP)
            out_arg_management(elem);
        else if (elem->type == REDIR_IN || elem->type == REDIR_HD)
            in_arg_management(elem);
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
}

int token_simplification(t_input *data)
{
    t_node  *elem;

    elem = data->args;
    if (quote_transformation(elem, data) == 1)
        return (1);
    if (general_simplification(elem, data) == 1)
        return (1);
    if (word_total_fusion(elem, data) == 1)
        return (1);
    if (word_quote_fusion(elem, data) == 1)
        return (1);
    if (delete_useless_wspace(elem, data) == 1)
        return (1);
    ms_token_print(data->args);
    return (0);
}
