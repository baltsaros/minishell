/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:36:15 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/05 13:23:42 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all_flags(t_node *elem)
{
	while (elem)
	{
		elem->flag = 0;
		elem = elem->next;
	}
}

int	is_p_closed(t_node *elem)
{
	while (elem)
	{
		if (elem->type == BR_R)
			return (0);
		elem = elem->next;
	}
	return (1);
}

t_node	*change_flags(t_node *elem, int type, int flag)
{
	if (elem->next && elem->next->type != type)
	{
		elem = elem->next;
		while (elem && elem->type != type)
		{
			elem->flag = flag;
			elem = elem->next;
		}
	}
	else if (elem->next)
		elem = elem->next;
	return (elem);
}

t_node	*change_flag_p(t_node *elem)
{
	if (elem->next && elem->next->type != BR_R)
	{
		elem = elem->next;
		if (!is_p_closed(elem))
		{
			while (elem && elem->type != BR_R)
			{
				elem->flag = B_QUOTE_P;
				elem = elem->next;
			}
		}
	}
	else if (elem->next)
		elem = elem->next;
	return (elem);
}

int	add_flags(t_node *elem)
{
	init_all_flags(elem);
	while (elem)
	{
		if (elem->type == QUOTE)
			elem = change_flags(elem, QUOTE, B_QUOTE);
		else if (elem->type == QUOTE_D)
			elem = change_flags(elem, QUOTE_D, B_QUOTE_D);
		else if (elem->type == BR_L)
			elem = change_flag_p(elem);
		if (!elem || !elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}
