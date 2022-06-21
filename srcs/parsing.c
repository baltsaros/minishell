/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/21 13:34:37 by mthiry           ###   ########.fr       */
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

int	free_all_and_error(t_input *data)
{
	free_data_line(data->line);
	//free_args(data->args);
	return (1);
}

t_node	*init_first_elem(char *line)
{

}

t_node	*parse_args(char *line)
{
	t_node 	*first_elem;
	t_node	*args;
	t_node	*new_con;
	int		i;

	first_elem = init_first_elem(line);
	i = 0;
	while (line[i])
	{

	}
	return (first_elem);
}

int	parsing(t_input *data, char *buf)
{
	int	i;

	i = 0;
	data->line = ft_split(buf, ' ');
	if (check_all(data) != 0)
		return (free_all_and_error(data));
	//data->args = parse_args(data->line);
	free_data_line(data->line);
	//if (!data->args)
	//	free_args(data->args);
	return (0);
}