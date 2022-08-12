/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:22:06 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 09:31:42 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in(t_node *args, t_cmd *elem, t_input *data)
{
	if (!args->next || is_the_next_is_in_arg(args) == 1)
		return (print_syntax_error_bool(args, data));
	if (args->next && args->next->type == IN_ARG)
	{
		if (init_in(args, elem, data) == 1)
			return (1);
	}
	else if (args->next->next && args->next->next->type == IN_ARG)
	{
		args = args->next;
		if (init_in(args, elem, data) == 1)
			return (1);
	}
	else if (args->next && (args->next->type == REDIR_OUT
			|| args->next->type == REDIR_AP))
		return (0);
	else
		return (print_syntax_error_bool(args, data));
	return (0);
}

int	redirection_out(t_node *args, t_cmd *elem, t_input *data)
{
	if (!args->next || is_the_next_is_out_arg(args) == 1)
		return (print_syntax_error_bool(args, data));
	if (args->next && args->next->type == OUT_ARG)
	{
		if (init_out(args, elem, data) == 1)
			return (1);
	}
	else if (args->next->next && args->next->next->type == OUT_ARG)
	{
		if (init_out(args, elem, data) == 1)
			return (1);
	}
	else if (args->next && (args->next->type == REDIR_IN
			|| args->next->type == REDIR_HD))
		return (0);
	else
		return (print_syntax_error_bool(args, data));
	return (0);
}

int	redirection_check(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->value && (args->type == REDIR_IN || args->type == REDIR_HD))
		return (redirection_in(args, elem, data));
	else if (args->value && (args->type == REDIR_OUT || args->type == REDIR_AP))
		return (redirection_out(args, elem, data));
	return (0);
}

t_node	*next_elem(t_node *args)
{
	t_node	*next_elem;

	next_elem = args;
	while (next_elem)
	{
		if (!next_elem->next)
			return (NULL);
		next_elem = next_elem->next;
		if (next_elem->prev && next_elem->prev->type == PIPE)
			break ;
	}
	return (next_elem);
}

int	get_len_cmd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
