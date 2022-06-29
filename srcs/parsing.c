/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/29 14:29:03 by mthiry           ###   ########.fr       */
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

t_cmd	*fill_elem(t_input *data, t_cmd *elem)
{
	int	i;

	i = 0;
	if (data->args->type == WORD)
		elem->cmd = ft_strdup(data->args->value);
	else
		return (NULL);
	i++;
	data->args = data->args->next;
	while (data->args && data->args->prev->value[0] != '|')
	{
		if (data->args->value[0] == '-')
			elem->cmd_flags = ft_strdup(data->args->value + 1);
		else if (data->args->type == WORD)
			elem->argument = ft_strdup(data->args->value);
		else if (!ft_strncmp(data->args->value, "<<", 2))
		{
			// Open Heredoc here
			data->args = data->args->next;
			i++;
			elem->delim = ft_strdup(data->args->value);
		}
		else if (data->args->value[0] == '<')
			elem->in = open(elem->argument, O_RDONLY);
		else if (data->args->value[0] == '>')
		{
			if (data->args->value[1] == '>')
				elem->out = open(elem->argument, O_WRONLY | O_CREAT | O_APPEND, 00644);
			else
				elem->out = open(elem->argument, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		}
		else if (data->args && data->args->value[0] == '|')
			elem->pipe = 1;
		i++;
		data->args = data->args->next;
	}
	elem->index = i;
	return (elem);
}

t_cmd	*parse_cmd(t_input *data)
{
	(void)data;
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;

	first_elem = init_empty_elem();
	first_elem = fill_elem(data, first_elem);
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