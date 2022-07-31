/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/25 09:27:35 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	general_simplification(t_node *elem)
{
	while (elem)
	{
		if (elem->type == WORD && !ft_strncmp(elem->value, "./", 2))
			elem->type = EXECUTABLE;
		else if ((elem->type == REDIR_OUT || elem->type == REDIR_AP) && elem->next)
			out_arg_management(elem);
		else if ((elem->type == REDIR_IN || elem->type == REDIR_HD) && elem->next)
			in_arg_management(elem);
		else if (elem->type == BR_L)
		{
			if (elem->next && elem->next->flag != B_QUOTE_P)
				elem->type = WORD;
			else if (!elem->next)
				elem->type = WORD;
		}
		else if (elem->type == BR_R)
		{
			if (elem->prev && elem->prev->flag != B_QUOTE_P)
				elem->type = WORD;
			else if (!elem->prev)
				elem->type = WORD;
		}
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
	if (word_total_fusion(elem, data) == 1)
		return (1);
	// ms_token_print(elem);
	if (quote_transformation(elem, data) == 1)
		return (1);
	if (general_simplification(elem) == 1)
		return (1);
	if (delete_useless_wspace(elem) == 1)
		return (1);
	// ms_token_print(elem);
	return (0);
}
