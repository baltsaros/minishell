/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:59 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 11:35:59 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// eof error for unclosed quotes and pipes
int	eof_error(char *msg, int check)
{
	if (check)
	{
		free(msg);
		write(2, "YAMSP: unexpected EOF while looking for matching `", 50);
		write(2, &check, 1);
		write(2, "'\n", 2);
	}
	write(2, "YAMSP: syntax error: ", 21);
	write(2, "unexpected end of file\n", 23);
	g_status = 2;
	return (1);
}

int	check_closed(t_input *data, char *str)
{
	int	type;

	data->i = 0;
	while (str[data->i])
	{
		if (str[data->i] == '\'' || str[data->i] == '\"')
		{
			type = str[data->i++];
			while (str[data->i] && str[data->i] != type)
				data->i++;
		}
		if (!str[data->i])
			return (1);
		data->i++;
	}
	if (str[data->i - 1] == '|')
		return (1);
	return (0);
}

// wait for an unclosed pipe to be closed
int	check_pipe(char **buf, char *msg, char c, t_input *data)
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
