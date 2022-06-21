/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/21 15:17:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// interesting: if p1 | p2 -> p2 always gets excuted, even if 1 doesnt exist or is not comaptible -> exit never works with pipe
// p1 only gets excecuted if p2 exists
// check for pipes
// check for redirects
// assign priority

int	check_all(t_input *data)
{
	int i;
	int er;

	i = 0;
	er = 0;
	if (!ft_strncmp(data->line[0], "|", 1))
	{
		write(1, "Error: parse error near `|'\n", 28);
		er++;
	}
	else
	{
		while (data->line[i])	
		{
			if (is_a_right_builtin(data->line[i]) != true && ft_strncmp(data->line[i], "|", 1))
			{
				write(1, "Error: command not found: ", 26);
				write(1, data->line[i], ft_strlen(data->line[i]));
				write(1, "\n", 1);
				er++;
			}
			i++;
		}
	}
	return (er);
}

int	parsing(t_input *data, char *buf)
{
	int	i;
	t_node *cmd_node;

	i = 0;
	data->line = ft_split(buf, ' ');
	//if (check_all(data) != 0)
	//	return (free_all_and_error(data));
	cmd_node = parse_args(data->line);
	if (!cmd_node)
	{
		free_data_line(data->line);
		return (1);
	}
	free_data_line(data->line);
	//data->cmds = init_cmds(cmd_node);
	free_args(cmd_node);
	return (0);
}