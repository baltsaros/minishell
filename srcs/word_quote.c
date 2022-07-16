#include "../include/minishell.h"

int word_quote_fusion(t_node *elem, t_input *data)
{
    while (elem)
    {
        printf("Readed: %s\n", elem->value);
        if (!is_between_d_quote(elem))
        {
            if (elem->next && elem->next->type == QUOTE_D)
            {
                if (elem->next->next && elem->next->next->type != WSPACE)
                {
                    elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
                    if (!elem->value)
                        return (1);
                    elem->next = update_next_and_prev(elem->next);
                }
            }
            if (elem->prev && elem->prev->type == QUOTE_D)
            {
                if (elem->prev->prev && elem->prev->prev->type != WSPACE)
                {
                    elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
                    if (!elem->value)
                        return (1);
                    elem->prev = update_prev_and_next(elem->prev);
                }
            }
        }
        if (!is_between_quote(elem))
        {
            if (elem->next && elem->next->type == QUOTE)
            {
                if (elem->next->next && elem->next->next->type != WSPACE)
                {
                    elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
                    if (!elem->value)
                        return (1);
                    elem->next = update_next_and_prev(elem->next);
                }
            }
            // if (elem->prev && elem->prev->type == QUOTE)
            // {
            //     if (elem->prev->prev && elem->prev->prev->type != WSPACE)
            //     {
            //         elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
            //         if (!elem->value)
            //             return (1);
            //         elem->prev = update_prev_and_next(elem->prev);
            //     }
            // }
        }

        // if (!elem->next)
        //     break ;
        elem = elem->next;
    }
    return (0);
}