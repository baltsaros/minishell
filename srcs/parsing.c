/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/21 19:02:31 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// interesting: if p1 | p2 -> p2 always gets excuted, even if 1 doesnt exist or is not comaptible -> exit never works with pipe
// p1 only gets excecuted if p2 exists
// check for pipes
// check for redirects
// assign priority

int	is_end_elem(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (0);
	if (c == '\0' || c == '\n')
		return (0);
	return (1);
}

int	get_nb_elem(char	*buf)
{
	int count;
	int	i;

	count = 1;
	i = 0;
	while (buf[i])
	{
		if (!is_end_elem(buf[i]))
		{
			count++;
			while (!is_end_elem(buf[i]))
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	parsing(t_input *data, char *buf)
{
	(void)data;
	//char	**line;
	
	buf = remove_white_spaces(buf);

	printf("%s\n", buf);
	printf("%d\n", get_nb_elem(buf));

	free(buf);
		
	return (0);
}