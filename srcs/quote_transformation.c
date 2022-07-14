#include "../include/minishell.h"

t_node  *fusion_all_between_quote(t_node *elem, t_input *data, int type)
{
    while (elem && (elem->type != DOLLAR && elem->type != PIPE))
    {
        elem = elem->next;
    }
    return (elem);
}

t_node  *quote_transformation(t_input   *data)
{
    t_node  *elem;

    elem = data->args;
    while (elem)
    {
        if (!is_between_d_quote(elem) || !is_between_quote(elem))
        {
            printf("Test\n");
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    while (elem->prev)
        elem = elem->prev;
    ms_token_print(elem);
    return (elem);
}