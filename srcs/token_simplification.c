/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/20 20:17:54 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar_management(t_node *elem, t_input *data)
{
	elem = dollar_token_simplification(elem, data);
	if (elem->type == ENV_VA)
		elem->value = ms_strdup(getenv(elem->value + 1), data);
	else if (elem->type == ENV_VA_BR)
		elem->value = ms_strdup(
				getenv(get_between_braces(elem, BRACES_L, BRACES_R)), data);
	else if (elem->type == ENV_P)
		elem->value = ms_strdup(get_between_braces(elem, BR_L, BR_R), data);
	else if (elem->type == ENV_P_EM)
	{
		elem->type = 0;
		free(elem->value);
		elem->value = ms_strdup(NULL, data);
	}
}

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

int	is_between_p(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == BR_L || args->type == BR_R)
		return (1);
	while (args->prev && args->type != BR_L && args->type != PIPE)
		args = args->prev;
	if (args->type == BR_L)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != BR_R && args->type != PIPE)
		args = args->next;
	if (args && args->type == BR_R)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

int	general_simplification(t_node *elem, t_input *data)
{
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == DOLLAR)
			dollar_management(elem, data);
		else if (!is_between_p(elem))
			elem->type = WORD;
		else if (elem->type == WORD && !ft_strncmp(elem->value, ".", 2))
			elem = executable_token_simplification(elem, data);
		else if (elem->type == REDIR_OUT || elem->type == REDIR_AP)
			out_arg_management(elem);
		else if (elem->type == REDIR_IN || elem->type == REDIR_HD)
			in_arg_management(elem);
		elem = elem->next;
	}
	return (0);
}

int	empty_when_only_quote(t_node	*elem, t_input	*data)
{
	(void)data;
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == QUOTE_D && elem->next && elem->next->type == QUOTE_D)
		{
			elem->type = EMPTY_ARG;
			ms_token_del(elem->next);
		}
		if (elem->type == QUOTE && elem->next && elem->next->type == QUOTE)
		{
			elem->type = EMPTY_ARG;
			ms_token_del(elem->next);
		}
		elem = elem->next;
	}
	return (0);
}

int	delete_useless_quote(t_node	*elem, t_input	*data)
{
	(void)data;
	while (elem)
	{
		if (elem->type == QUOTE_D)
			elem->type = 0;
		if (elem->next && elem->next->type == QUOTE)
			elem->type = 0;;
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
	// printf("1: ");
	// ms_token_print(data->args);
    if (quote_transformation(elem, data) == 1)
        return (1);
	// printf("2: ");
	// ms_token_print(data->args);
    if (general_simplification(elem, data) == 1)
        return (1);
	// printf("3: ");
	// ms_token_print(data->args);
    if (word_total_fusion(elem, data) == 1)
        return (1);
	// printf("4: ");
	// ms_token_print(data->args);
    if (word_quote_fusion(elem, data) == 1)
        return (1);
	// printf("5: ");
	// ms_token_print(data->args);
    if (delete_useless_wspace(elem, data) == 1)
        return (1);
	// printf("6: ");
    // ms_token_print(data->args);
	if (empty_when_only_quote(elem, data) == 1)
		return (1);
	// printf("7: ");
	// ms_token_print(data->args);
	if (delete_useless_quote(elem, data) == 1)
		return (1);
	// printf("8: ");
	// ms_token_print(data->args);
    return (0);
}
