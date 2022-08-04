/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 14:19:09 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	delete_useless_wspace(t_node *elem)
{
	while (elem)
	{
		while (elem->next && elem->type == WSPACE)
			elem = delete_node(elem);
		if (!elem->next && elem->type == WSPACE)
		{
			elem = ms_token_del(elem);
			return (0);
		}
		elem = elem->next;
	}
	return (0);
}
