#include "../include/minishell.h"

t_node  *executable_token_simplification(t_node *elem, t_input *data)
{
    if (elem->next && elem->next->type == SLASH)
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        // update_next_and_prev(elem);
        elem = ms_token_del(elem->next);
        if (elem->next && elem->type == WORD)
        {
            elem->type = EXECUTABLE;
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            // update_next_and_prev(elem);
            elem = ms_token_del(elem->next);
        }
        else if (elem->next && elem->type != WSPACE)
        {
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            // update_next_and_prev(elem);
            elem = ms_token_del(elem->next);
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
        if (!elem->value)
            return (NULL);
        // elem = update_next_and_prev(elem);
        elem = ms_token_del(elem->next);
    }
    return (elem);
}

t_node  *aster_after_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    if (!elem->value)
        return (NULL);
    // elem = update_next_and_prev(elem);
    elem = ms_token_del(elem->next);
    return (elem);
}

t_node  *aster_before_token_simplification(t_node *elem, t_input  *data)
{
    elem->type = ASTER_WORD;
    elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
    if (!elem->value)
        return (NULL);
    // elem = update_next_and_prev(elem);
    elem = ms_token_del(elem->next);
    if (elem->next)
    {
        elem = aster_after_token_simplification(elem, data);
        if (!elem)
            return (NULL);
    }
    return (elem);
}

int general_simplification(t_node   *elem, t_input  *data)
{
    while (elem)
    {
        if (elem->type == DOLLAR)
        {
            elem = dollar_token_simplification(elem, data);
            if (!elem)
                return (1);
            elem->value = ms_strdup(getenv(elem->value + 1), data);
        }
        else if (elem->type == ASTER)
        {
            if (elem->prev && elem->prev->type == WORD_AST)
            {
                elem = aster_before_token_simplification(elem->prev, data);
                if (!elem)
                    return (1);
            }
            if (elem->next && elem->next->type == WORD_AST)
            {
                elem = aster_after_token_simplification(elem, data);
                if (!elem)
                    return (1);
            }
            data->args = elem;
        }
        else if (elem->type == WORD && !ft_strncmp(elem->value, ".", 2))
        {
            elem = executable_token_simplification(elem, data);
            if (!elem)
                return (1);
        }
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
    ms_token_print(data->args);
    return (0);
}
