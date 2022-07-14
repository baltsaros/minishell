#include "../include/minishell.h"

t_node  *nothing_between_quote(t_node *elem, t_input *data)
{
    elem->value = ms_strdup("", data);
    if (elem->next->type == QUOTE_D)
    {
        if (elem->next->next && elem->next->next->type == QUOTE_D)
        {
            if (elem->next->next->next)
            {
                elem->next = elem->next->next->next;
                // free quotes
            }
            else
            {
                elem->next = NULL;
                // free quotes
            }
        }
    }

    else if (elem->next->type == QUOTE)
    {
        if (elem->next->next && elem->next->next->type == QUOTE)
        {
            if (elem->next->next->next)
            {
                elem->next = elem->next->next->next;
                // free quotes
            }
            else
            {
                elem->next = NULL;
                // free quotes
            }
        }
    }
    return (elem);
}

t_node  *jump_after_quote(t_node    *elem)
{
    while (elem->type != QUOTE_D && elem->type != QUOTE)
        elem = elem->next;
    if (elem->next)
        return (elem->next);
    return (NULL);
}

t_node  *get_all_between_quote(t_node *elem, t_input  *data, t_node *tmp, int type)
{
    elem->value = ms_strdup("", data);
    elem->value = ms_strjoin_free(elem->value, tmp->value, data);
    if (!elem->value)
        return (NULL);
    if (tmp->next && tmp->next->type != type)
    {
        tmp = tmp->next;
        while (tmp->type != type)
        {
            elem->value = ms_strjoin_free(elem->value, tmp->value, data);
            if (!elem->value)
                return (NULL);
            tmp = tmp->next;
        }
    }
    elem->next = jump_after_quote(tmp);
    if (elem->next)
        elem->next->prev = elem;
    return (elem);
}

t_node  *quote_transformation(t_input   *data)
{
    t_node  *elem;

    elem = data->args;
    while (elem)
    {
        if (elem->type == QUOTE_D || elem->type == QUOTE)
        {
            if (elem->prev && elem->prev->type == DOLLAR
                && (is_between_d_quote(elem->prev) && is_between_quote(elem->prev)))
            {
                elem = elem->prev;
                elem->type = WORD;
                if (elem->next->next && elem->next->next->type != QUOTE_D)
                {
                    elem = get_all_between_quote(elem, data, elem->next->next, QUOTE_D);
                    if (!elem)
                        return (NULL);
                }
                else if (elem->next->next && elem->next->next->type != QUOTE)
                {
                    elem = get_all_between_quote(elem, data, elem->next->next, QUOTE);
                    if (!elem)
                        return (NULL);
                }
                else
                    elem = nothing_between_quote(elem, data);
            }
            else if (elem->type == QUOTE_D)
            {
                if (elem->next->type == QUOTE_D)
                {
                    printf("Hee hee\n");
                    elem->type = WORD;
                    // elem = update_next_and_prev(elem);
                    // elem = update_prev_and_next(elem);
                    // elem->value = ms_strdup("", data);
                }
                printf("Finito\n");
            }
            else if (elem->type == QUOTE)
            {
                if (elem->next->type == QUOTE)
                {
                    elem->type = WORD;
                    // elem = update_next_and_prev(elem);
                    // elem = update_prev_and_next(elem);
                    // elem->value = ms_strdup("", data);
                }
            }
        }
        else if (!is_between_d_quote(elem))
        {
            printf("What the fuck\n");
            if (elem->next && elem->next->type != QUOTE_D)
            {
                printf("GO\n");
                elem = get_all_between_quote(elem, data, elem, QUOTE);
                if (!elem)
                    return (NULL);
            }
            else
            {
                printf("Je passe a la tele\n");
                elem = update_next_and_prev(elem);
                elem = update_prev_and_next(elem);
            }
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    printf("C'est fini\n");
    if (elem->prev)
    {
        while (elem->prev)
            elem = elem->prev;
    }

    printf("ELEM A LA FIN: %s\n", elem->value);

    ms_token_print(elem);
    return (elem);
}