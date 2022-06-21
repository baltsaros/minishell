/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:38:20 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/20 17:00:52 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(t_node *args)
{
	t_node *tmp;

	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp);
	}
}

void	free_data_line(char **line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

bool	is_a_right_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (true);
	else if (!ft_strncmp(cmd, "-n", 2))
		return (true);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (true);
	else if (!ft_strncmp(cmd, "export", 6))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (true);
	else if (!ft_strncmp(cmd, "env", 3))
		return (true);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (true);
	return (false);
}

