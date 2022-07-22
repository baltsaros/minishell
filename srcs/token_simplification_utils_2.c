/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 10:34:50 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	delete_useless_wspace(t_node *elem, t_input *data)
{
	int	type;

	while (elem)
	{
		while (elem->next && elem->type == WSPACE)
		{
			data->node_tmp = elem;
			elem = elem->next;
			ms_token_del(data->node_tmp);
		}
		if (elem && (elem->type == QUOTE || elem->type == QUOTE_D))
		{
			type = elem->type;
			elem = elem->next;
			is_between_quote(elem, type);
		}
		elem = elem->next;
	}
	ms_token_print(elem);
	return (0);
}

// int	delete_useless_wspace(t_node *elem, t_input *data)
// {
// 	(void)data;
// 	while (elem)
// 	{
// 		if (!elem->next)
// 			break ;
// 		if (elem->next && elem->next->type == WSPACE
// 			&& (is_between_d_quote(elem->next) && is_between_quote(elem->next)))
// 			ms_token_del(elem->next);
// 		if (elem->next && elem->next->type == 0)
// 			ms_token_del(elem->next);
// 		elem = elem->next;
// 	}
// 	return (0);
// }
