/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 10:12:22 by mthiry           ###   ########.fr       */
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
		return ("");
	return (str);
}

void	become_word_and_more(t_node	*elem, t_input	*data)
{
	if (!elem->prev || (!elem->next
			|| (elem->next && elem->next->type == WSPACE)))
		elem->type = WORD;
	elem = dollar_token_simplification(elem, data);
}

void	empty_env_management(t_node	*elem, t_input	*data)
{
	elem->type = 0;
	free(elem->value);
	elem->value = ms_strdup(NULL, data);
}

int	delete_useless_empty_args(t_node *elem)
{
	while (elem)
	{
		if (elem->type == WSPACE
			&& (elem->next && !elem->next->value)
			&& (elem->next->next && elem->next->next->value))
		{
			while (elem->next && !elem->next->value)
			{
				delete_node(elem->next);
				if (!elem->next)
					break ;
			}
		}
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}

int	delete_useless_wspace(t_node *elem)
{
	if (!ft_strncmp(elem->value, "", 2))
	{
		elem->type = 0;
		elem = elem->next;
	}
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
