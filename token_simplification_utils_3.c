/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:55:27 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/12 15:40:40 by abuzdin          ###   ########.fr       */
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

// for cases like: cmd <> f1
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
	else if (elem && elem->type == WORD && elem->value && data->j == 1)
	{
		fd = open(elem->value, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (error_check_noexit(fd, elem->value, data))
			return (1);
		close(fd);
	}
	return (0);
}

// for cases like: <> f1
static int	dredir_nocmd(t_node *elem, t_input *data)
{
	int		fd;
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

// check double redirection <>
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
