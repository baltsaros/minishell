/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:39:24 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/20 14:39:25 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*fusion_all_between_d_quote(t_node *elem, t_input *data)
{
	t_node	*tmp;

	if (elem->type == DOLLAR)
		return (elem);
	tmp = elem->next;
	elem->type = WORD;
	while (tmp && (tmp->type != DOLLAR && tmp->type != QUOTE_D))
	{
		if (tmp->type == WORD && (tmp->prev && tmp->prev->type == DOLLAR))
			break ;
		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
		tmp = tmp->next;
	}
	elem->next = tmp;
	return (elem);
}

t_node	*fusion_all_between_quote(t_node *elem, t_input *data)
{
	t_node	*tmp;

	tmp = elem->next;
	elem->type = WORD;
	while (tmp && tmp->type != QUOTE)
	{
		elem->value = ms_strjoin_free(elem->value, tmp->value, data);
		tmp = tmp->next;
	}
	elem->next = tmp;
	return (elem);
}

int	quote_transformation(t_node *elem, t_input *data)
{
	while (elem)
	{
		if (!is_between_d_quote(elem))
			elem = fusion_all_between_d_quote(elem, data);
		else if (!is_between_quote(elem))
			elem = fusion_all_between_quote(elem, data);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}
