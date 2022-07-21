/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:21 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/21 22:22:48 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_std(t_input *data, int in, int out)
{
	int	ret;

	if (in > 0)
	{
		ret = dup2(data->cmds->in, STDIN_FILENO);
		error_check(ret, "In dup2_in ", 12, data);
	}
	if (out > 0)
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

char	*ms_strjoin_free(char *rest, char *buf, t_input *data)
{
	char	*unis;
	size_t	i;
	size_t	j;

	if (!rest || !buf)
		return (0);
	data->j = ft_strlen(rest) + ft_strlen(buf) + 1;
	unis = ms_malloc(sizeof(*unis) * data->j, data);
	i = 0;
	while (rest[i])
	{
		unis[i] = rest[i];
		++i;
	}
	j = 0;
	while (buf[j])
	{
		unis[i + j] = buf[j];
		++j;
	}
	unis[j + i] = '\0';
	free(rest);
	return (unis);
}

char	*ms_charjoin_free(char *line, char b, t_input *data)
{
	size_t	i;
	char	*unis;

	i = 0;
	while (line[i])
		++i;
	unis = ms_malloc(sizeof(*unis) * (i + 2), data);
	i = 0;
	while (line[i])
	{
		unis[i] = line[i];
		++i;
	}
	unis[i] = b;
	unis[i + 1] = 0;
	free(line);
	return (unis);
}
