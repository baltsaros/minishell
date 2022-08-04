/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/04 10:26:18 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
