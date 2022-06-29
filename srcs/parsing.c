/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/29 21:51:38 by mthiry           ###   ########.fr       */
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
	elem->in_arg = NULL;
	elem->out = 1;
	elem->out_arg = NULL;
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
		else if (data->args->type == WORD && elem->in == 0 && elem->out == 1
				&& elem->pipe == -1)
		{
			printf("ARGUMENTS\n");
		}
		else if (!ft_strncmp(data->args->value, "<<", 2))
		{
			// Open Heredoc here
			data->args = data->args->next;
			i++;
			elem->delim = ft_strdup(data->args->value);
		}
		else if (data->args->value[0] == '<')
		{
			data->args = data->args->next;
			i++;
			elem->in_arg = ft_strdup(data->args->value);
			elem->in = open(elem->in_arg, O_RDONLY);
		}
		else if (data->args->value[0] == '>')
		{
			if (data->args->value[1] == '>')
			{
				data->args = data->args->next;
				i++;
				elem->out_arg = ft_strdup(data->args->value);
				elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
			}
			else
			{
				data->args = data->args->next;
				i++;
				elem->out_arg = ft_strdup(data->args->value);
				elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
			}
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
		//if (data->cmds->arguments == NULL)
		//	printf("argument[0]: (null)\n");
		//else
		//{
			for (int i = 0; data->cmds->argument; i++)
			{
				printf("argument[%d]: %s\n", i, data->cmds->argument->value);
				data->cmds->argument = data->cmds->argument->next;
			}
		//}
		printf("delim: %s\n", data->cmds->delim);
		printf("in: %d\n", data->cmds->in);
		printf("in arg: %s\n", data->cmds->in_arg);
		printf("out: %d\n", data->cmds->out);
		printf("out arg: %s\n", data->cmds->out_arg);
		printf("pipe: %d\n", data->cmds->pipe);
		printf("index: %d\n", data->cmds->index);
		printf("[NEXT]\n");
		data->cmds = data->cmds->next;
	}
	//if (syntax_checker(data->args) == 1)
	//	return (1);
	return (0);
}