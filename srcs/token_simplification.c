#include "../include/minishell.h"

t_node  *executable_token_simplification(t_node *elem, t_input *data)
{
    if (elem->next && elem->next->type == SLASH)
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        update_next_and_prev(elem);
        if (elem->next && elem->type == WORD)
        {
            elem->type = EXECUTABLE;
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            update_next_and_prev(elem);
        }
        else if (elem->next && elem->type != WSPACE)
        {
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            update_next_and_prev(elem);
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

int word_quote_fusion(t_node *elem, t_input *data)
{
    while (elem)
    {
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
        // else if (!is_between_quote(elem))
        // {

        // }
        if (!elem->next)
            break ;
        elem = elem->next;
    }
    return (0);
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
            else if (elem->next && elem->next->type == WORD_AST)
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