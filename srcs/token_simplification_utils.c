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

t_node  *executable_token_simplification(t_node *elem, t_input *data)
{
    if (elem->next && elem->next->type == SLASH)
    {
        elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
        elem = ms_token_del(elem->next);
        if (elem->next && elem->type == WORD)
        {
            elem->type = EXECUTABLE;
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            elem = ms_token_del(elem->next);
        }
        else if (elem->next && elem->type != WSPACE)
        {
            elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
            elem = ms_token_del(elem->next);
        }
    }
    return (elem);
}

int get_braces_size(t_node  *elem, int type1, int type2)
{
    int i;
    int size;

    i = 0;
    size = 0;
    while (elem->value[i] != type1)
        i++;
    i++;
    while (elem->value[i] != type2)
    {
        size++;
        i++;
    }
    return (size);
}

char    *get_between_braces(t_node  *elem, int type1, int type2)
{
    char    *str;
    int     size;
    int     i;
    int     j;

    printf("Heeeeeeeeeeee heeeeeeeeeeeeeeeeeeeeeee\n");
    size = get_braces_size(elem, type1, type2);
    i = 0;
    j = 0;
    str = (char *) malloc ((size + 1) * sizeof(char));
    if (!str)
        return (NULL);
    while (elem->value[i] != type1)
        i++;
    i++;
    while (elem->value[i] != type2)
    {
        str[j] = elem->value[i];
        i++;
        j++; 
    }
    str[j] = '\0';
    return (str);
}