/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:47:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/10 21:00:52 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_node *tmp, t_cmd *arg, t_input *data)
{
	t_cmd	*new_con;

	while (tmp)
	{
		tmp = next_elem(tmp);
		if (!tmp)
			break ;
		new_con = init_elem(tmp, data);
		if (new_con)
		{
			new_con->prev = arg;
			arg->next = new_con;
			arg = arg->next;
		}
	}
}

t_cmd	*parse_cmd(t_input *data)
{
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_node	*tmp;

	tmp = data->args;
	if (tmp->type == 999)
		return (NULL);
	while (tmp)
	{
		first_elem = init_elem(tmp, data);
		if (first_elem)
			break ;
		tmp = next_elem(tmp);
	}
	if (!first_elem)
		return (NULL);
	arg = first_elem;
	init_all(tmp, arg, data);
	return (first_elem);
}

int	parsing(t_input *data)
{
	data->cmds = parse_cmd(data);
	if (!data->cmds || !data->exec)
		return (1);
	// t_cmd	*tmp;
	// tmp = data->cmds;
	// while (tmp)
	// {
	// 	for (int i = 0; tmp->cmd[i]; i++)
	// 		printf("cmd[%d]: %s\n", i, tmp->cmd[i]);
	// 	printf("len_cmd: %d\n", tmp->len_cmd);
	// 	printf("delim: %s\n", tmp->delim);
	// 	printf("in: %d\n", tmp->in);
	// 	printf("in arg: %s\n", tmp->in_arg);
	// 	printf("out: %d\n", tmp->out);
	// 	printf("out arg: %s\n", tmp->out_arg);
	// 	printf("pipe: %d\n", tmp->pipe);
	// 	printf("[NEXT]\n");
	// 	tmp = tmp->next;
	// }
	return (0);
}
