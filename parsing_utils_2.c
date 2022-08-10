/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:41:09 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/10 16:25:11 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// reads from stdin and saves it in tmp file; stops in case of ctrl+d or ctrl+c
void	ms_heredoc(char *limiter, t_cmd *elem, t_input *data)
{
	char	*line;

	if (signal(SIGINT, signal_hd) == SIG_ERR)
		error_check(-1, "", data);
	elem->in = open("heredoc.tmp", O_RDWR | O_CREAT | O_APPEND, 0777);
	error_check(elem->in, "heredoc", data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		hd_write(data, line, elem->in);
		free(line);
	}
	close(elem->in);
	exit(0);
}

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
		return (print_syntax_error_bool(args, data));
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		error_check(-1, "", data);
	data->pid = fork();
	if (error_check_noexit(data->pid, "", data))
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
	if (error_check_noexit(elem->in, "heredoc", data))
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
		if (error_check_noexit(elem->in, elem->in_arg, data))
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
		if (error_check_noexit(elem->out, elem->out_arg, data))
			return (1);
		return (0);
	}
	else if (args->type == REDIR_OUT)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (error_check_noexit(elem->out, elem->out_arg, data))
			return (1);
		return (0);
	}
	return (1);
}
