/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:21 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 10:05:41 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_std(t_input *data, int in, int out)
{
	int	ret;

	if (in > 0)
	{
		ret = dup2(data->cmds->in, IN);
		error_check(ret, data->cmds->in_arg, data);
	}
	if (out > 1)
	{
		ret = dup2(data->cmds->out, OUT);
		error_check(ret, data->cmds->out_arg, data);
	}
}

void	close_fds(int fd1, int fd2, int param)
{
	if (param)
	{
		if (fd1)
			close(fd1);
		if (fd2 > 1)
			close(fd2);
	}
	if (!param)
	{
		close(fd1);
		close(fd2);
	}
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

int	is_builtin(t_input *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmds->cmd[0], data->builtins[i].name))
			++i;
		else
			return (1);
	}
	return (0);
}
