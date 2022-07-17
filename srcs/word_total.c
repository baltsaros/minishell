#include "../include/minishell.h"

int fusion_with_prev_elem(t_node  *elem, t_input  *data)
{
    (void)data;
    while (elem && elem->prev && (elem->prev->type != WSPACE 
        && elem->prev->type != QUOTE_D && elem->prev->type != QUOTE))
    {
        elem->value = ft_strjoin(elem->prev->value, elem->value);
        ms_token_del(elem->prev);
    }
    return (0);
}

int fusion_with_next_elem(t_node  *elem, t_input  *data)
{
    while (elem && elem->next && (elem->next->type != WSPACE 
        && elem->next->type != QUOTE_D && elem->next->type != QUOTE))
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        ms_token_del(elem->next);
    }
    return (0);
}

int fusion_env_va(t_node    *elem, t_input  *data)
{
    while (elem && elem->next && elem->next->type == ENV_VA)
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        ms_token_del(elem->next);
    }
    return (0);
}

int word_total_fusion(t_node   *elem, t_input  *data)
{
    while (elem)
    {
        if ((elem->type != WSPACE && elem->type != QUOTE && elem->type != QUOTE_D)
            && elem->prev && elem->prev->type != WSPACE)
            fusion_with_prev_elem(elem, data);
        if ((elem->type != WSPACE && elem->type != QUOTE && elem->type != QUOTE_D)
            && elem->next && elem->next->type != WSPACE)
            fusion_with_next_elem(elem, data);
        if (elem->type == ENV_VA && elem->next && elem->next->type == ENV_VA)
            fusion_env_va(elem, data);
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
}