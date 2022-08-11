/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_4.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:53:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 09:54:42 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion_between_quote(t_node *elem)
{
	if (elem->flag == B_QUOTE_P || elem->flag == B_QUOTE)
	{
		if (elem->type == DOLLAR_R)
		{
			free(elem->value);
			elem->value = ft_strdup("$?");
		}
		elem->type = WORD;
	}
}
