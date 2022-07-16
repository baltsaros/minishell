#include "../include/minishell.h"

int word_total_fusion(t_node   *elem, t_input  *data)
{
    while (elem)
    {
        if ((elem->type != WSPACE && elem->type != QUOTE && elem->type != QUOTE_D)
            && elem->prev && elem->prev->type != WSPACE)
        {
            while (elem && elem->prev && (elem->prev->type != WSPACE 
                && elem->prev->type != QUOTE_D && elem->prev->type != QUOTE))
            {
                elem->value = ms_strjoin_free(elem->prev->value, elem->value, data);
                if (!elem->value)
                    return (1);
                elem = update_prev_and_next(elem);
            }
        }
        if ((elem->type != WSPACE && elem->type != QUOTE && elem->type != QUOTE_D)
            && elem->next && elem->next->type != WSPACE)
        {
            while (elem && elem->next && (elem->next->type != WSPACE 
                && elem->next->type != QUOTE_D && elem->next->type != QUOTE))
            {
                elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
                if (!elem->value)
                    return (1);
                elem = update_next_and_prev(elem);
            }
        }
        if (elem->type == ENV_VA && elem->next && elem->next->type == ENV_VA)
        {
            while (elem && elem->next && elem->next->type == ENV_VA)
            {
                elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
                if (!elem->value)
                    return (1);
                elem = update_next_and_prev(elem);
            }
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
}