#include "../include/minishell.h"

int word_quote_fusion(t_node *elem, t_input *data)
{
	t_node	*first;
	char	*str;
	int		type;

	while (elem && elem->type != QUOTE && elem->type != QUOTE_D)
		elem = elem->next;
	if (elem)
		type = elem->type;
	else if (!elem)
		return (0);
	if (elem->next && elem->next->type != type)
		first = elem->next;
	else
		return (0);
	if (elem->prev && (elem->prev->type == WORD || elem->prev->type == ASTER))
	{
		str = ms_strdup(elem->value, data);
		free(elem->value);
		if (elem->prev->type == ASTER)
			first->type = ASTER;
		first->value = ft_strjoin(elem->prev->value, first->value);
		free(str);
		// elem = ms_token_del(elem->prev);
		elem->prev->type = 0;

	}
	elem = elem->next->next;
	while (elem && elem->type != type)
	{
		first->value = ms_strjoin_free(first->value, elem->value, data);
		elem = ms_token_del(elem);
	}
	if (elem->next && (elem->next->type == WORD || elem->next->type == ASTER))
	{
		if (elem->next->type == ASTER)
			first->type = ASTER;
		first->value = ms_strjoin_free(first->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	return (0);
}