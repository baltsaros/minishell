/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/20 14:30:08 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	delete_useless_wspace(t_node *elem, t_input *data)
{
	(void)data;
	while (elem)
	{
		if (elem->next && elem->next->type == WSPACE
			&& (is_between_d_quote(elem->next) && is_between_quote(elem->next)))
			ms_token_del(elem->next);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}
