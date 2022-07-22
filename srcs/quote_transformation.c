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

// t_node	*fusion_all_between_d_quote(t_node *elem, t_input *data)
// {
// 	t_node	*tmp;

// 	if (elem->type == DOLLAR)
// 		return (elem);
// 	tmp = elem->next;
// 	elem->type = WORD_DQ;
// 	while (tmp && tmp->type != DOLLAR && tmp->type != QUOTE_D)
// 	{
// 		if (tmp->type == WORD && (tmp->prev && tmp->prev->type == DOLLAR))
// 			break ;
// 		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
// 		tmp = tmp->next;
// 	}
// 	elem->next = tmp;
// 	return (elem);
// }

// t_node	*fusion_all_between_quote(t_node *elem, t_input *data)
// {
// 	t_node	*tmp;

// 	tmp = elem->next;
// 	elem->type = WORD_Q;
// 	while (tmp && tmp->type != QUOTE)
// 	{
// 		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
// 		tmp = tmp->next;
// 	}
// 	elem->next = tmp;
// 	return (elem);
// }

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
		// if (tmp->type == DOLLAR && tmp->next && tmp->next->type == WORD)
		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
		tmp = delete_node(tmp);
		
	}
	if (tmp && tmp->type == type)
		elem = tmp->next;
	return (elem);
}

int	quote_transformation(t_node *elem, t_input *data)
{
	
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == QUOTE_D || elem->type == QUOTE)
			elem = fuse_between_quotes(elem, data, elem->type);
		else
			elem = elem->next;
	}
	return (0);
}
