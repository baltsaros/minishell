/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:47:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 14:43:48 by abuzdin          ###   ########.fr       */
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
	return (0);
}
