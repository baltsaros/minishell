/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/07/03 20:05:26 by mthiry           ###   ########.fr       */
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
	elem->argument_buf = NULL;
	elem->cmd_flags = NULL;
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

t_cmd	*fill_elem(t_node	*args, t_cmd *elem)
{
	int	i;

	i = 0;
	elem->cmd = ft_split(elem->argument_buf, ' ');
	if (!elem->cmd)
	{
		free(elem->argument_buf);
		return (NULL);
	}
	free(elem->argument_buf);
	while (args && args->type != PIPE)
	{
		if (args->value[0] == '-')
		{
			elem->cmd_flags = ft_strdup(args->value + 1);
			if (!elem->cmd_flags)
				return (NULL);
		}
		else if (args->value[0] == '<')
		{
			if (!ft_strncmp(args->value, "<<", 2))
			{
				//Open Heredoc here
				i++;
				args =  args->next;
				elem->delim = ft_strdup(args->value);
				if (!elem->delim)
					return (NULL);
			}
			else if (args->value[1] == '\0')
			{
				i++;
				args = args->next;
				elem->in_arg = ft_strdup(args->value);
				if (!elem->in_arg)
					return (NULL);
				elem->in = open(elem->in_arg, O_RDONLY);
			}
		}
		else if (args->value[0] == '>')
		{
			if (!ft_strncmp(args->value, ">>", 2))
			{
				i++;
				args = args->next;
				elem->out_arg = ft_strdup(args->value);
				if (!elem->out_arg)
					return (NULL);
				elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
			}
			else if (args->value[1] == '\0')
			{
				i++;
				args = args->next;
				elem->out_arg = ft_strdup(args->value);
				if (!elem->out_arg)
					return (NULL);
				elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
			} 
		}
		else if (args->next)
		{
			if (args->next->type == PIPE)
				elem->pipe = 1;
		}
		i++;
		args = args->next;
	}
	if (args && args->type == PIPE)
		i += 2;
	elem->index = i;
	return (elem);
}

t_cmd	*init_elem(t_node *args)
{
	t_cmd	*elem;

	elem = init_empty_elem();
	if (!elem)
		return (NULL);
	elem->argument_buf = get_args(args);
	if (!elem->argument_buf)
		return (NULL);
	elem = fill_elem(args, elem);
	if (!elem)
		return (NULL);
	return (elem);
}

t_cmd	*parse_cmd(t_input *data)
{
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;
	int		index;
	int		i;

	first_elem = init_elem(data->args);
	if (!first_elem)
		return (NULL);
	arg = first_elem;
	index = first_elem->index;
	i = 0;
	//while (data->args)
	//{
	//	while (i != index)
	//	{
	//		data->args = data->args->next;
	//		i++;
	//	}
	//	i = 0;
	//	new_con = init_elem(data->args);
	//	if (!new_con)
	//		return (NULL);
	//	new_con->prev = arg;
	//	arg->next = new_con;
	//	arg = arg->next;
	//}
	(void)arg;
	(void)new_con;
	(void)i;
	(void)index;
	return (first_elem);
}

int	parsing(t_input *data)
{
	data->cmds = parse_cmd(data);
	if (!data->cmds)
		return (1);
		
	while (data->cmds)
	{
		for (int i = 0; data->cmds->cmd[i]; i++)
			printf("cmd[%d]: %s\n", i, data->cmds->cmd[i]);
		printf("cmd_flags: %s\n", data->cmds->cmd_flags);
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