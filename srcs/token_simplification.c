#include "../include/minishell.h"

int	is_between_d_quote(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == QUOTE_D)
		return (1);
	while (args->prev && args->type != QUOTE_D && args->type != PIPE)
		args = args->prev;
	if (args->type == QUOTE_D)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != QUOTE_D && args->type != PIPE)
		args = args->next;
	if (args && args->type == QUOTE_D)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

int	is_between_quote(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == QUOTE)
		return (1);
	while (args->prev && args->type != QUOTE && args->type != PIPE)
		args = args->prev;
	if (args->type == QUOTE)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != QUOTE && args->type != PIPE)
		args = args->next;
	if (args && args->type == QUOTE)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

t_node  *update_next_and_prev(t_node *elem)
{
    t_node  *second_tmp;
    t_node  *tmp;

    tmp = elem->next;
    if (elem->next->next)
    {
        second_tmp = elem->next->next;
        elem->next = second_tmp;
        second_tmp->prev = elem;
        // free tmp here
    }
    else
    {
        elem->next = NULL;
        // free tmp here
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

int token_simplification(t_input *data)
{
    t_node  *elem;

    elem = data->args;
    while (elem)
    {
        printf("Readed: %s\n", elem->value);
        if (elem->type == DOLLAR)
        {
            elem = dollar_token_simplification(elem, data);
            if (!elem)
                return (1);
            data->args = elem;
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
    printf("END: %s\n", elem->value);
    if (elem->prev)
    {
        while (elem->prev)
            elem = elem->prev;
        printf("ELEM PREV EXIST\n");
    }
    // data->args = elem;
    ms_token_print(data->args);
    return (0);
}