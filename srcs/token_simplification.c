#include "../include/minishell.h"

t_node  *dollar_token_simplification(t_node *elem, t_input  *data)
{
    if (elem->next && elem->next->type == WORD)
    {
        elem->type = ENV_VA;
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        if (!elem->value)
            return (NULL);
        elem = update_next_and_prev(elem);
    }
    return (elem);
}

t_node  *aster_after_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    if (!elem->value)
        return (NULL);
    elem = update_next_and_prev(elem);
    return (elem);
}

t_node  *aster_before_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    if (!elem->value)
        return (NULL);
    elem = update_next_and_prev(elem);
    if (elem->next)
    {
        elem = aster_after_token_simplification(elem, data);
        if (!elem)
            return (NULL);
    }
    return (elem);
}

int token_simplification(t_input *data)
{
    t_node  *elem;

    elem = quote_transformation(data);
    elem = data->args;
    while (elem)
    {
        if (elem->type == DOLLAR)
        {
            elem = dollar_token_simplification(elem, data);
            if (!elem)
                return (1);
        }
        // else if (elem->type == ASTER)
        // {
        //     if (elem->prev && elem->prev->type == WORD_AST)
        //     {
        //         elem = aster_before_token_simplification(elem->prev, data);
        //         if (!elem)
        //             return (1);
        //     }
        //     else if (elem->next && elem->next->type == WORD_AST)
        //     {
        //         elem = aster_after_token_simplification(elem, data);
        //         if (!elem)
        //             return (1);
        //     }
        //     data->args = elem;
        // }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    if (elem->prev)
    {
        while (elem->prev)
            elem = elem->prev;
    }
    ms_token_print(data->args);
    return (0);
}