/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 15:04:37 by abuzdin          ###   ########.fr       */
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
		if (!elem->next)
			break ;
		if (elem->type == WORD && !ft_strncmp(elem->value, "./", 2))
			elem->type = EXECUTABLE;
		else if (elem->type == REDIR_OUT || elem->type == REDIR_AP)
			out_arg_management(elem);
		else if (elem->type == REDIR_IN || elem->type == REDIR_HD)
			in_arg_management(elem);
		elem = elem->next;
	}
	return (0);
}

int	token_simplification(t_input *data)
{
	t_node	*elem;

    elem = data->args;
	// printf("1 before everything: ");
	// ms_token_print(data->args);
	if (expanding_variables(elem, data) == 1)
		return (1);
	// printf("2 expanding variables: ");
	// ms_token_print(data->args);
	if (word_total_fusion(elem, data) == 1)
 		return (1);
	// printf("3 word total fusion: ");
	// ms_token_print(data->args);
	if (quote_transformation(elem, data) == 1)
		return (1);
	// printf("4 quote transformation: ");
	// ms_token_print(data->args);
    if (general_simplification(elem) == 1)
		return (1);
	// printf("5 general simplification: ");
	// ms_token_print(data->args);
	if (delete_useless_wspace(elem) == 1)
		return (1);
	// printf("6 after delete useless wspace: ");
    // ms_token_print(data->args);
    return (0);
}
