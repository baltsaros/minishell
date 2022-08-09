/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:50 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 10:26:48 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_error(char *str)
{
	g_status = 127;
	write(2, "env: ", 5);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
}

// print only envp that have values
int	yo_env(t_input *data)
{
	t_env	*tmp;

	tmp = data->envp_n;
	if (data->cmds->cmd[1])
	{
		env_error(data->cmds->cmd[1]);
		return (g_status);
	}
	while (tmp)
	{
		if (tmp->value)
		{
			write(data->cmds->out, tmp->type, ft_strlen(tmp->type));
			write(data->cmds->out, "=", 1);
			write(data->cmds->out, tmp->value, ft_strlen(tmp->value));
			write(data->cmds->out, "\n", 1);
		}
		tmp = tmp->next;
	}
	g_status = 0;
	return (g_status);
}
