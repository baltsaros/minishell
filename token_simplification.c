/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/10 21:10:42 by abuzdin          ###   ########.fr       */
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

static int	dredir_cmd(t_node *elem, t_input *data)
{
	int	fd;

	if (elem->next && elem->next->type == REDIR_OUT)
	{
		elem = delete_node(elem);
		elem = delete_node(elem);
	}
	while (elem && elem->type == WSPACE)
		elem = elem->next;
	if (elem && elem->type == WORD && elem->value && data->j > 1)
	{
		fd = open(elem->value, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (error_check_noexit(fd, elem->value, data))
			return (1);
		close(fd);
		elem = ms_token_del(elem);
	}
	return (0);
}

static int	dredir_nocmd(t_node *elem, t_input *data)
{
	int	fd;
	t_node	*in;
	t_node	*out;

	in = elem;
	if (elem->next && elem->next->type == REDIR_OUT)
	{
		out = elem->next;
		elem = elem->next->next;
	}
	while (elem && elem->type == WSPACE)
		elem = elem->next;
	if (elem && elem->type == WORD && elem->value)
	{
		fd = open(elem->value, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (error_check_noexit(fd, elem->value, data))
			return (1);
		close(fd);
		elem->type = 999;
		in->type = 999;
		out->type = 999;
	}
	return (0);
}

int	check_dredir(t_node *elem, t_input *data)
{
	int	ret;

	while (elem)
	{
		data->j = 0;
		while (elem && elem->type != REDIR_IN)
		{
			if (elem->type == WORD)
				data->j++;
			else if (elem->type == PIPE)
				data->j = 0;
			elem = elem->next;
		}
		if (!elem)
			return (0);
		if (data->j > 0)
			ret = dredir_cmd(elem, data);
		else if (data->j == 0)
			ret = dredir_nocmd(elem, data);
		if (ret == 1)
			return (1);
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
	ms_token_print(elem);
	return (0);
}
