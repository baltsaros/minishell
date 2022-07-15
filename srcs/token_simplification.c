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

t_node  *word_transformation_simplification(t_node *elem, t_input *data)
{
    while (elem)
    {
        if (!is_between_d_quote(elem) || !is_between_quote(elem))
        {
            if (elem->type != ENV_VA && elem->prev->type == QUOTE_D)
            {
                if (elem->prev->prev && elem->prev->prev->type != WSPACE && elem->prev->prev->type != ENV_VA)
                {
                    elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
                    if (!elem->value)
                        return (NULL);
                    update_prev_and_next(elem->prev);
                }
            }
            else if (elem->type != ENV_VA && elem->prev->type == QUOTE)
            {
                if (elem->prev->prev && elem->prev->prev->type != WSPACE && elem->prev->prev->type != ENV_VA)
                {
                    elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
                    if (!elem->value)
                        return (NULL);
                    update_prev_and_next(elem->prev);
                }
            }
            if (elem->type != ENV_VA && elem->next->type == QUOTE_D)
            {
                if (elem->next->next && elem->next->next->type != WSPACE && elem->next->next->type != ENV_VA)
                {
                    elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
                    if (!elem->value)
                        return (NULL);
                    update_next_and_prev(elem->next);
                }
            }
            else if (elem->type != ENV_VA && elem->next->type == QUOTE)
            {
                if (elem->next->next && elem->next->next->type != WSPACE && elem->next->next->type != ENV_VA)
                {
                    elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
                    if (!elem->value)
                        return (NULL);
                    update_next_and_prev(elem->next);
                }
            }
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    if (elem->prev)
    {
        while (elem->prev)
            elem = elem->prev;
    }
    return (elem);
}

int token_simplification(t_input *data)
{
    t_node  *elem;

    elem = quote_transformation(data);
    if (!elem)
        return (1);
    elem = data->args;
    while (elem)
    {
        if (elem->type == DOLLAR)
        {
            elem = dollar_token_simplification(elem, data);
            if (!elem)
                return (1);
        }
        else if (elem->type == ASTER)
        {
            if (elem->prev && elem->prev->type == WORD_AST)
            {
                elem = aster_before_token_simplification(elem->prev, data);
                if (!elem)
                    return (1);
            }
            else if (elem->next && elem->next->type == WORD_AST)
            {
                elem = aster_after_token_simplification(elem, data);
                if (!elem)
                    return (1);
            }
            data->args = elem;
        }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    if (elem->prev)
    {
        while (elem->prev)
            elem = elem->prev;
    }
    elem = word_transformation_simplification(elem, data);
    if (!elem)
        return (1);

    printf("ELEM  VALUE: %s\n", elem->value);

    ms_token_print(data->args);
    return (0);
}