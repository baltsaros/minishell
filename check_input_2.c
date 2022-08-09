/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:59 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/09 15:22:53 by abuzdin          ###   ########.fr       */
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
		free(msg);
	write(2, "YAMSP: syntax error: ", 21);
	write(2, "unexpected end of file\n", 23);
	g_status = 2;
	write(1, "\n", 1);
	return (1);
	// exit(g_status);
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
