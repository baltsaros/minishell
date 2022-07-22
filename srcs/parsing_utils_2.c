/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:41:09 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 12:59:03 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_size_cmd(t_node	*args)
{
	int	i;
	int	type;

	i = 0;
	while (args && args->type != PIPE)
	{
		if (args->type == QUOTE || args->type == QUOTE_D)
		{
			type = args->type;
			args = args->next;
			is_between_quote(args, type);
			args = args->next;
		}
		if (args->type != WSPACE)
			i++;
		if (args->type == ENV_VA && args->prev && args->prev->type == ENV_VA)
			i--;
		if (args->type == IN_ARG || args->type == OUT_ARG
			|| args->type == DOLLAR || !args->value || args->type == 0)
			i--;
		args = args->next;
	}
	return (i);
}

int	init_hd(t_node	*args, t_cmd	*elem, t_input *data)
{
	args = args->next;
	elem->delim = ms_strdup(args->value, data);
	if (!elem->delim)
		return (print_syntax_error_bool(args));
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		error_check(-1, "in signals ", 11, data);
	data->pid = fork();
	if (error_check_noexit(data->pid, "In fork hd ", 11, data))
		return (1);
	if (data->pid == 0)
		ms_heredoc(elem->delim, elem, data);
	elem->in_arg = ms_strdup("heredoc.tmp", data);
	waitpid(data->pid, &g_status, 0);
	if (WEXITSTATUS(g_status) == 130)
	{
		unlink("heredoc.tmp");
		return (1);
	}
	elem->in = open("heredoc.tmp", O_RDONLY);
	if (error_check_noexit(elem->in, "in parsing open ", 16, data))
		return (1);
	unlink("heredoc.tmp");
	return (0);
}

int	init_in(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->type == REDIR_HD)
		return (init_hd(args, elem, data));
	else if (args->type == REDIR_IN)
	{
		if (elem->in)
			close(elem->in);
		args = args->next;
		elem->in_arg = ms_strdup(args->value, data);
		elem->in = open(elem->in_arg, O_RDONLY);
		if (error_check_noexit(elem->in, "in parsing open ", 16, data))
			return (1);
		return (0);
	}
	return (1);
}

int	init_out(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->type == REDIR_AP)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (error_check_noexit(elem->out, "in parsing open ", 16, data))
			return (1);
		return (0);
	}
	else if (args->type == REDIR_OUT)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (error_check_noexit(elem->out, "in parsing open ", 16, data))
			return (1);
		return (0);
	}
	return (1);
}
