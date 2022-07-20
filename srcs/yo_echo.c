/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:47 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/20 09:31:48 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	show_rvalue(char **str, int status, t_input *data)
{
	if (!ft_strncmp(*str, "$?", 3))
	{
		free(*str);
		if (status > 255)
			status = (status >> 8) & 0xff;
		*str = ft_itoa(status);
		alloc_check_small(*str, data);
	}
}

static void	echo_with_flag(t_cmd *com, int status, t_input *data)
{
	int	i;

	i = 2;
	while (com->cmd[i])
	{
		show_rvalue(&com->cmd[i], status, data);
		write(com->out, com->cmd[i], ft_strlen(com->cmd[i]));
		++i;
	}
}

static void	echo_without_flag(t_cmd *com, int status, t_input *data)
{
	int	i;

	i = 1;
	while (com->cmd[i])
	{
		show_rvalue(&com->cmd[i], status, data);
		write(com->out, com->cmd[i], ft_strlen(com->cmd[i]));
		write(com->out, " ", 1);
		++i;
	}
	write(com->out, "\n", 1);
}

int	yo_echo(t_input *data)
{
	if (!data->cmds->cmd[1])
		write(data->cmds->out, "\n", 1);
	else if (strncmp(data->cmds->cmd[1], "-n", 2) == 0)
		echo_with_flag(data->cmds, g_status, data);
	else
		echo_without_flag(data->cmds, g_status, data);
	g_status = 0;
	return (0);
}
