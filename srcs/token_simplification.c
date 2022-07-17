#include "../include/minishell.h"

t_node  *executable_token_simplification(t_node *elem, t_input *data)
{
    if (elem->next && elem->next->type == SLASH)
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        ms_token_del(elem->next);
        if (elem->next && elem->type == WORD)
        {
            elem->type = EXECUTABLE;
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            ms_token_del(elem->next);
        }
        else if (elem->next && elem->type != WSPACE)
        {
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            ms_token_del(elem->next);
        }
    }
    return (elem);
}

t_node  *dollar_token_simplification(t_node *elem, t_input  *data)
{
    if (elem->next && elem->next->type == WORD)
    {
        elem->type = ENV_VA;
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        ms_token_del(elem->next);
    }
    return (elem);
}

t_node  *aster_after_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    ms_token_del(elem->next);
    return (elem);
}

t_node  *aster_before_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    ms_token_del(elem->next);
    if (elem->next)
        elem = aster_after_token_simplification(elem, data);
    return (elem);
}

int general_simplification(t_node   *elem, t_input  *data)
{
    while (elem)
    {
        if (elem->type == DOLLAR)
        {
            elem = dollar_token_simplification(elem, data);
            elem->value = ms_strdup(getenv(elem->value + 1), data);
        }
        else if (elem->type == ASTER)
        {
            if (elem->prev && elem->prev->type == WORD_AST)
                elem = aster_before_token_simplification(elem->prev, data);
            else if (elem->next && elem->next->type == WORD_AST)
                elem = aster_after_token_simplification(elem, data);
            data->args = elem;
        }
        else if (elem->type == WORD && !ft_strncmp(elem->value, ".", 2))
            elem = executable_token_simplification(elem, data);
        else if (elem->type == REDIR_OUT || elem->type == REDIR_AP)
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
        else if (elem->type == REDIR_IN || elem->type == REDIR_HD)
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
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
}

int delete_useless_wspace(t_node *elem, t_input *data)
{
    (void)data;
    while (elem)
    {
        if (elem->next && elem->next->type == WSPACE
            && (is_between_d_quote(elem->next) && is_between_quote(elem->next)))
            ms_token_del(elem->next);
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