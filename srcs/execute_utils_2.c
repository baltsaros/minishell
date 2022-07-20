/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:21 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/20 09:30:22 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_std(t_input *data, int in, int out)
{
	int	ret;

	if (in)
	{
		ret = dup2(data->cmds->in, STDIN_FILENO);
		error_check(ret, "In dup2_in ", 12, data);
	}
	if (out)
	{
		ret = dup2(data->cmds->out, STDOUT_FILENO);
		error_check(ret, "In dup2_out ", 13, data);
	}
}

void	close_fds(int fd1, int fd2)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
}
