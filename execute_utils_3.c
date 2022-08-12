/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:53:41 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 10:07:32 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hd_estatus(int *i, int out)
{
	char	*tmp;

	if (g_status > 255)
		g_status = (g_status >> 8) & 0xff;
	tmp = ft_itoa(g_status);
	write(out, tmp, ft_strlen(tmp));
	free(tmp);
	++(*i);
	return (0);
}

static int	hd_expansion(t_input *data, char *str, int out, int *i)
{
	int		start;
	t_env	*tmp;

	start = *i;
	if (str[start] == '?')
		return (hd_estatus(i, out));
	while (str[*i] && ft_isalnum(str[*i]))
		++(*i);
	if (start == *i)
		return (1);
	data->tmp = ms_strndup(str + start, *i - start, data);
	tmp = data->envp_n;
	while (tmp)
	{
		if (tmp->value && !ft_strcmp(tmp->type, data->tmp))
		{
			write(out, tmp->value, ft_strlen(tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
	free(data->tmp);
	return (0);
}

void	hd_write(t_input *data, char *str, int out)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			++i;
			if (hd_expansion(data, str, out, &i))
				write(out, "$", 1);
		}
		if (str[i] && str[i] != '$')
		{
			write(out, &str[i], 1);
			++i;
		}
	}
	write(out, "\n", 1);
}
