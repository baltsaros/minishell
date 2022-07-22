/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:39:24 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 11:43:09by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_node	*delete_node(t_node *elem)
{
	t_node	*tmp;

	if (!elem || !elem->next)
		return (elem);
	tmp = elem;
	elem = elem->next;
	elem->prev = tmp->prev;
	elem->prev->next = elem;
	free(tmp->value);
	free(tmp);
	return (elem);
}

t_node	*fuse_next_elem(t_node *elem, t_node *tmp, t_input *data)
{
	tmp = elem;
	elem = elem->prev->prev;
	elem->value = ms_strjoin_free(elem->value, tmp->value, data);
	tmp = delete_node(tmp);
	elem = elem->next->next;
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
	if (elem->type == WORD || elem->type == SLASH)
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
	tmp = delete_node(tmp);
	elem->value = ms_strjoin_free(str, str_2, data);
	free(str_2);
	return (elem);
}

int	quote_transformation(t_node *elem, t_input *data)
{
	
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == QUOTE_D || elem->type == QUOTE)
		{
			if (elem->prev && (elem->prev->type == WORD || elem->prev->type == SLASH))
				fuse_prev_elem(elem, data, elem->type);
			elem = fuse_between_quotes(elem, data, elem->type);
			if (!elem->next)
				break ;
		}
		else
			elem = elem->next;
	}
	return (0);
}
