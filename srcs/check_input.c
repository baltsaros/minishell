/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:59 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/20 09:30:00 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	check_field(t_input *data, char *str)
{
	int		type;

	type = 0;
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
		check_pipe(&data->buf, "> ", '|', data);
}

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
