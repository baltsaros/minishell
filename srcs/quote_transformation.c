/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:39:24 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/25 09:54:24 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*delete_node(t_node *elem)
{
	t_node	*tmp;

	if (!elem)
		return (NULL);
	if (!elem->next)
		return (elem);
	tmp = elem;
	elem = elem->next;
	if (!tmp->prev)
		elem->prev = NULL;
	else
		elem->prev = tmp->prev;
	if (elem->prev)
		elem->prev->next = elem;
	free(tmp->value);
	free(tmp);
	return (elem);
}

t_node	*fuse_next_elem(t_node *elem, t_node *tmp, t_input *data)
{
	tmp = elem;
	if (!elem->prev->prev)
		return (elem);
	elem = elem->prev->prev;
	elem->value = ms_strjoin_free(elem->value, tmp->value, data);
	elem = ms_token_del(tmp);
	if (elem->next)
		elem = elem->next;
	return (elem);
}

t_node	*fuse_between_quotes(t_node *elem, t_input *data, int type)
{
	t_node	*tmp;

	elem = elem->next;
	if (elem->type == type)
	{
		if (elem->next)
			elem = elem->next;
		return (elem);
	}
	tmp = elem->next;
	elem->type = WORD;
	while (tmp && tmp->type != type)
	{
		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
		tmp = delete_node(tmp);
	}
	if (tmp && tmp->type == type)
		elem = tmp->next;
	if (elem && (elem->type == WORD || elem->type == SLASH))
		elem = fuse_next_elem(elem, tmp, data);
	return (elem);
}

t_node	*fuse_prev_elem(t_node *elem, t_input *data, int type)
{
	char	*str;
	char	*str_2;
	t_node	*tmp;

	tmp = elem->prev;
	elem = elem->next;
	if (elem->type == type)
	{
		if (elem->next)
			elem = elem->next;
		return (elem);
	}
	str = ms_strdup(tmp->value, data);
	str_2 = elem->value;
	elem->value = ms_strjoin_free(str, str_2, data);
	tmp->type = 0;
	// delete_node(tmp);
	free(str_2);
	return (elem);
}

int	quote_transformation(t_node *elem, t_input *data)
{
	while (elem)
	{
		if (!elem->next)
			break ;
		if ((elem->type == QUOTE_D && elem->next
				&& elem->next->type == QUOTE_D)
			|| (elem->type == QUOTE && elem->next && elem->next->type == QUOTE))
		{
			elem->type = EMPTY_ARG;
			ms_token_del(elem->next);
		}
		else if (elem->type == QUOTE_D || elem->type == QUOTE)
		{
			if (elem->prev && (elem->prev->type == WORD
					|| elem->prev->type == SLASH))
				fuse_prev_elem(elem, data, elem->type);
			elem = fuse_between_quotes(elem, data, elem->type);
			if (!elem || !elem->next)
				break ;
		}
		else
			elem = elem->next;
	}
	return (0);
}
