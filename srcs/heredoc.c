/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:09:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/06 13:16:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	endhere(char *buffer, char *end)
{
	while (*end && *buffer && *buffer == *end)
	{
		end++;
		buffer++;
	}
	if (!*end && !*buffer)
		return (0);
	else
		return (1);
}

void	wr_heredoc(int fd, char *end)
{
	char	*buffer;

	buffer = "";
	while (buffer)
	{
		buffer = readline("heredoc>");
		if (!buffer || endhere(buffer, end) == 0)
		{
			free(buffer);
			break ;
		}
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
}

int	create_heredoc(char *end)
{
	int	fd;

	fd = open("/tmp/iwe.tmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
	wr_heredoc(fd, end);
	close(fd);
	fd = open("/tmp/iwe.tmp", O_RDONLY, 00777);
	unlink("/tmp/iwe.tmp");
	return (fd);
}

