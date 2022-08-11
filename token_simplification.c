/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 13:20:10 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_empty_args(t_node *elem)
{
	while (elem)
	{
		if (elem->type != EMPTY_ARG && !elem->value)
			elem->type = EMPTY_ARG;
		if (elem->type == EMPTY_ARG && elem->next
			&& elem->next->type == EMPTY_ARG)
		{
			while (elem->next && elem->next->type == EMPTY_ARG)
				delete_node(elem->next);
		}
		if (elem->type != EMPTY_ARG && elem->type != WSPACE
			&& elem->type != QUOTE_D && elem->type != QUOTE)
		{
			if (elem->prev && elem->prev->type == EMPTY_ARG)
				elem->prev->type = 0;
			if (elem->next && elem->next->type == EMPTY_ARG)
				delete_node(elem->next);
		}
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}

void	ft_executable(t_node	*elem)
{
	if (elem->value && elem->type == WORD
		&& !ft_strncmp(elem->value, "./", 2))
		elem->type = EXECUTABLE;
}

int	general_simplification(t_node *elem)
{
	while (elem)
	{
		ft_executable(elem);
		if (elem->type == BR_L)
		{
			if ((!elem->next) || (elem->next && elem->next->flag != B_QUOTE_P))
				elem->type = WORD;
		}
		else if (elem->type == BR_R)
		{
			if ((!elem->prev) || (elem->prev && elem->prev->flag != B_QUOTE_P))
				elem->type = WORD;
		}
		else if ((elem->type == REDIR_OUT
				|| elem->type == REDIR_AP) && elem->next)
			out_arg_management(elem);
		else if ((elem->type == REDIR_IN
				|| elem->type == REDIR_HD) && elem->next)
			in_arg_management(elem);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}

int	token_simplification(t_input *data)
{
	t_node	*elem;

	elem = data->args;
	if (add_flags(elem) == 1)
		return (1);
	if (expanding_variables(elem, data) == 1)
		return (1);
	if (check_dredir(elem, data) == 1)
		return (1);
	if (delete_useless_empty_args(elem) == 1)
		return (1);
	if (word_total_fusion(elem, data) == 1)
		return (1);
	if (quote_transformation(elem, data) == 1)
		return (1);
	if (general_simplification(elem) == 1)
		return (1);
	if (manage_empty_args(elem) == 1)
		return (1);
	if (delete_useless_wspace(elem) == 1)
		return (1);
	return (0);
}
