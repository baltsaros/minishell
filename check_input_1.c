/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:59 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/07 13:43:14 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// wait for an unclosed pipe to be closed
static int	check_pipe(char **buf, char *msg, char c, t_input *data)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		if (!tmp)
			return (eof_error(msg, 0));
		*buf = ms_charjoin_free(*buf, '\n', data);
		*buf = ms_strjoin_free(*buf, tmp, data);
		if (!ft_strchr(tmp, c) || !ft_strcmp(tmp, "|"))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (0);
}

// wait for unclosed quotes to be closed
static int	read_after(char **buf, char c, t_input *data)
{
	char	*tmp;
	char	*msg;

	if (c == '\'')
		msg = ms_strdup("quote> ", data);
	else
		msg = ms_strdup("dquote> ", data);
	while (1)
	{
		tmp = readline(msg);
		if (!tmp)
			return (eof_error(msg, 1));
		*buf = ms_charjoin_free(*buf, '\n', data);
		*buf = ms_strjoin_free(*buf, tmp, data);
		if (ft_strchr(tmp, c))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	free(msg);
	return (0);
}

// syntax check for pipe
static int	before_pipe(char *str, int i)
{
	if (!str[i])
	{
		write(2, "YAMSP: ", 7);
		write(2, "syntax error near unexpected token `|'\n", 39);
		g_status = 2;
		return (1);
	}
	while (check_charset(str[i], " \f\n\r\t\v"))
		--i;
	if (str[i] && check_charset(str[i], "><"))
	{
		write(2, "YAMSP: ", 7);
		write(2, "syntax error near unexpected token `|'\n", 39);
		g_status = 2;
		return (1);
	}
	return (0);
}

static int	check_pipe_quotes(t_input *data, char *str, int type)
{
	while (str[data->i])
	{
		if (str[data->i] == '\'' || str[data->i] == '\"')
		{
			type = str[data->i++];
			while (str[data->i] && str[data->i] != type)
				data->i++;
			if (!str[data->i] && (type == '\'' || type == '\"'))
			{
				if (read_after(&data->buf, type, data))
					return (1);
				break ;
			}
		}
		data->i++;
	}
	if (str[data->i - 1] == '|')
	{
		if (before_pipe(str, data->i - 2))
			return (1);
		if (check_pipe(&data->buf, "> ", '|', data))
			return (1);
	}
	return (0);
}

// check for unclosed quotes and pipes
// i had to add fork in order to handle signals properly
int	check_field(t_input *data, char *str)
{
	int	type;
	int	ret;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		error_check(-1, "", data);
	data->i = 0;
	type = 0;
	ret = 1;
	data->pid = fork();
	if (error_check_noexit(data->pid, "", data))
		return (1);
	if (data->pid == 0)
	{
		if (signal(SIGINT, signal_hd) == SIG_ERR)
			error_check(-1, "", data);
		ret = check_pipe_quotes(data, str, type);
		return (ret);
	}
	waitpid(data->pid, &g_status, 0);
	if (WEXITSTATUS(g_status) == 130)
		return (ret);
	else
		exit(g_status);
}
