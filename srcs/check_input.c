/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:59 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/26 10:11:42 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// wait for an unclosed pipe to be closed
static int	check_pipe(char **buf, char *msg, char c, t_input *data)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
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
static int	read_after(char **buf, char *msg, char c, t_input *data)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ms_charjoin_free(*buf, '\n', data);
		*buf = ms_strjoin_free(*buf, tmp, data);
		if (ft_strchr(tmp, c))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (0);
}

// syntax check for pipe
static int	before_pipe(char *str, int i)
{
	printf("before pipe\n");
	if (!str[i])
	{
		write(2, "YAMSP: ", 7);
		write(2, "syntax error near unexpected token `|'\n", 39);
		g_status = 258;
		return (1);
	}
	while (check_charset(str[i], " \f\n\r\t\v"))
		--i;
	if (str[i] && check_charset(str[i], "><"))
	{
		write(2, "YAMSP: ", 7);
		write(2, "syntax error near unexpected token `|'\n", 39);
		g_status = 258;
		return (1);
	}
	return (0);
}

// check for unclosed quotes and pipes
int	check_field(t_input *data, char *str)
{
	int	type;

	data->i = 0;
	while (str[data->i])
	{
		if (str[data->i] == '\'' || str[data->i] == '\"')
		{
			type = str[data->i];
			data->i++;
			while (str[data->i] && str[data->i] != type)
				data->i++;
			if (!str[data->i] && type == '\'')
				read_after(&data->buf, "quote> ", type, data);
			else if (!str[data->i] && type == '\"')
				read_after(&data->buf, "dquote> ", type, data);
		}
		data->i++;
	}
	if (str[data->i - 1] == '|')
	{
		if (before_pipe(str, data->i - 2))
			return (1);
		check_pipe(&data->buf, "> ", '|', data);
	}
	return (0);
}

// check for white space in input
int	is_right_buf(char *buf)
{
	int	i;

	i = 0;
	if (buf[0] == '\0')
		return (1);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
			&& buf[i] != '\v' && buf[i] != '\f' && buf[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
