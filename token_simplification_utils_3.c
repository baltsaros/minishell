/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:55:27 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/08 15:57:02 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_arg_management(t_node *elem)
{
	if (elem->next && (elem->next && elem->next->type == WSPACE))
	{
		elem = elem->next;
		if (elem->next && (elem->next->type != PIPE
				&& elem->next->type != REDIR_IN
				&& elem->next->type != REDIR_OUT
				&& elem->next->type != REDIR_HD
				&& elem->next->type != REDIR_AP))
			elem->next->type = OUT_ARG;
	}
	else if (elem->next && (elem->next->type != PIPE
			&& elem->next->type != REDIR_IN
			&& elem->next->type != REDIR_OUT
			&& elem->next->type != REDIR_HD
			&& elem->next->type != REDIR_AP))
		elem->next->type = OUT_ARG;
}

void	in_arg_management(t_node *elem)
{
	if (elem->next && (elem->next && elem->next->type == WSPACE))
	{
		elem = elem->next;
		if (elem->next && (elem->next->type != PIPE
				&& elem->next->type != REDIR_IN
				&& elem->next->type != REDIR_OUT
				&& elem->next->type != REDIR_HD
				&& elem->next->type != REDIR_AP))
			elem->next->type = IN_ARG;
	}
	else if (elem->next && (elem->next->type != PIPE
			&& elem->next->type != REDIR_IN
			&& elem->next->type != REDIR_OUT
			&& elem->next->type != REDIR_HD
			&& elem->next->type != REDIR_AP))
		elem->next->type = IN_ARG;
}
