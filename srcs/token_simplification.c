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

t_node  *env_va_fusion(t_node   *elem, t_input  *data)
{
    (void)data;
    while (elem)
    {
        if (elem->type == ENV_VA && elem->next && elem->next->type == ENV_VA)
        {
            while (elem && elem->next && elem->next->type == ENV_VA)
            {
                elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
                if (!elem->value)
                    return (NULL);
                elem = update_next_and_prev(elem);
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
            printf("SALUT\n");
            ms_strdup(elem->value, data);
            if (elem->next && elem->next->type == SLASH)
            {
                ms_strjoin_free(elem->value, elem->next->value, data);
                update_next_and_prev(elem);
                if (elem->next && elem->type == WORD)
                {
                    elem->type = EXECUTABLE;
                    ms_strjoin_free(elem->value, elem->next->next->value, data);
                    update_next_and_prev(elem);
                }
                else if (elem->next && elem->type != WSPACE)
                {
                    ms_strjoin_free(elem->value, elem->next->next->value, data);
                    update_next_and_prev(elem);
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
    elem = env_va_fusion(elem, data);
    ms_token_print(data->args);
    return (0);
}