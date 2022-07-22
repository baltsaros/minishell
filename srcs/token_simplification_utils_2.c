/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 14:01:29 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_between_p(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == BR_L || args->type == BR_R)
		return (1);
	while (args->prev && args->type != BR_L && args->type != PIPE)
		args = args->prev;
	if (args->type == BR_L)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != BR_R && args->type != PIPE)
		args = args->next;
	if (args && args->type == BR_R)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

char	*ms_getenv(char *var, t_input *data)
{
	t_env	*tmp;
	char	*str;

	tmp = data->envp_n;
	while (tmp && ft_strcmp(tmp->type, var))
		tmp = tmp->next;
	if (tmp)
		str = tmp->value;
	else
		return (NULL);
	return (str);
}

int	delete_useless_wspace(t_node *elem, t_input *data)
{
	int	type;

	while (elem)
	{
		while (elem->next && elem->type == WSPACE)
		{
			data->node_tmp = elem;
			elem = elem->next;
			ms_token_del(data->node_tmp);
		}
		if (elem && (elem->type == QUOTE || elem->type == QUOTE_D))
		{
			type = elem->type;
			elem = elem->next;
			is_between_quote(elem, type);
		}
		elem = elem->next;
	}
	return (0);
}
