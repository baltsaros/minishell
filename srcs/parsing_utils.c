/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:38:20 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/21 18:10:06 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (0);
	if (c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (1);
}

char	*remove_white_spaces(char *buf)
{
	char	*new_buf;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (buf[i++])
		if (is_white_space(buf[i]))
			count++;
	new_buf = (char *) malloc (count * sizeof(char));
	if (!new_buf)
		return(NULL);
	i = 0;
	while(buf[i] && j < count)
	{
		if (!is_white_space(buf[i]))
			i++;
		else
			new_buf[j++] = buf[i++];
	}
	free(buf);
	return (new_buf);
}

