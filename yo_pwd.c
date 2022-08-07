/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:03 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/07 13:48:50 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	yo_pwd(t_input *data)
{
	char	*ret;

	ret = NULL;
	ret = getcwd(NULL, 0);
	if (!ret)
	{
		write(2, "YAMSP: ", 7);
		perror("pwd");
		g_status = 1;
	}
	else
	{
		write(data->cmds->out, ret, ft_strlen(ret));
		write(data->cmds->out, "\n", 1);
		g_status = 0;
		free(ret);
	}
	return (0);
}
