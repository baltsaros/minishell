/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/29 01:05:22 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*init_empty_elem(void)
{
	t_cmd	*elem;

	elem = (t_cmd *) malloc (sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->cmd_flags = NULL;
	elem->argument = NULL;
	elem->delim = NULL;
	elem->in = 0;
	elem->out = 1;
	elem->pipe = -1;
	elem->index = 0;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_cmd	*parse_cmd(t_input *data)
{
	(void)data;
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;

	first_elem = init_empty_elem();
	(void)arg;
	(void)new_con;
	return (first_elem);
}

int	parsing(t_input *data)
{
	data->cmds = parse_cmd(data);
	if (!data->cmds)
		return (1);
		
	while (data->cmds)
	{
		printf("cmd: %s\n", data->cmds->cmd);
		printf("cmd_flags: %s\n", data->cmds->cmd_flags);
		printf("argument: %s\n", data->cmds->argument);
		printf("delim: %s\n", data->cmds->delim);
		printf("in: %d\n", data->cmds->in);
		printf("out: %d\n", data->cmds->out);
		printf("pipe: %d\n", data->cmds->pipe);
		printf("index: %d\n", data->cmds->index);
		printf("[NEXT]\n");
		data->cmds = data->cmds->next;
	}
	//if (syntax_checker(data->args) == 1)
	//	return (1);
	return (0);
}