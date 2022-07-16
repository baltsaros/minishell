#include "../include/minishell.h"

t_node  *fusion_all_between_d_quote(t_node *elem, t_input *data)
{
    t_node  *tmp;

    if (elem->type == DOLLAR)
        return (elem);
    tmp = elem->next;
    elem->type = WORD;
    while (tmp && (tmp->type != DOLLAR && tmp->type != QUOTE_D))
    {
        if (tmp->type == WORD && (tmp->prev && tmp->prev->type == DOLLAR))
            break ;
        elem->value = ms_strjoin_free(elem->value, tmp->value, data);
        if (!elem->value)
            return (NULL);
        tmp = tmp->next;
    }
    elem->next = tmp;
    return (elem);
}

t_node  *fusion_all_between_quote(t_node *elem, t_input *data)
{
    t_node  *tmp;

    tmp = elem->next;
    elem->type = WORD;
    while (tmp && tmp->type != QUOTE)
    {
        elem->value = ms_strjoin_free(elem->value, tmp->value, data);
        if (!elem->value)
            return (NULL);
        tmp = tmp->next;
    }
    elem->next = tmp;
    return (elem);
}

int quote_transformation(t_node *elem, t_input   *data)
{
    while (elem)
    {
        if (!is_between_d_quote(elem))
        {
            elem = fusion_all_between_d_quote(elem, data);
            if (!elem)
                return (1);
        }
        else if (!is_between_quote(elem))
        {
            elem = fusion_all_between_quote(elem, data);
            if (!elem)
                return (1);
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
}