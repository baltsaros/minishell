/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_total.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:23:06 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/08 14:00:00 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fusion_with_prev_elem(t_node *elem, t_input *data)
{
	char	*str;

	while (elem && elem->prev
		&& (elem->next->type != PIPE && elem->prev->type != WSPACE
			&& elem->prev->type != QUOTE_D && elem->prev->type != QUOTE
			&& elem->prev->type != REDIR_IN && elem->prev->type != REDIR_OUT
			&& elem->prev->type != REDIR_HD && elem->prev->type != REDIR_AP))
	{
		if (!elem->prev->value)
			ms_token_del(elem->prev);
		else
		{
			str = ms_strdup(elem->value, data);
			free(elem->value);
			elem->value = ft_strjoin(elem->prev->value, str);
			free(str);
			ms_token_del(elem->prev);
		}
	}
	return (0);
}

int	fusion_with_next_elem(t_node *elem, t_input *data)
{
	while (elem && elem->next
		&& (elem->next->type != PIPE && elem->next->type != WSPACE
			&& elem->next->type != QUOTE_D && elem->next->type != QUOTE
			&& elem->next->type != REDIR_IN && elem->next->type != REDIR_OUT
			&& elem->next->type != REDIR_HD && elem->next->type != REDIR_AP))
	{
		if (!elem->next->value)
			ms_token_del(elem->next);
		else
		{
			elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
			ms_token_del(elem->next);
		}
	}
	return (0);
}

int	fusion_env_va(t_node *elem, t_input *data)
{
	while (elem && elem->next && elem->next->type == ENV_VA)
	{
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	return (0);
}

int	word_total_fusion(t_node *elem, t_input *data)
{
	while (elem && elem->type != PIPE)
	{
		if (!elem->next)
			break ;
		if (elem->type == BR_L || elem->type == BR_R
			|| elem->type == BRACES_L || elem->type == BRACES_R)
			elem->type = WORD;
		if ((elem->type != WSPACE && elem->type != QUOTE
				&& elem->type != QUOTE_D
				&& elem->type != REDIR_IN && elem->type != REDIR_OUT
				&& elem->type != REDIR_HD && elem->type != REDIR_AP)
			&& elem->prev && elem->prev->type != WSPACE)
			fusion_with_prev_elem(elem, data);
		if ((elem->type != WSPACE && elem->type != QUOTE
				&& elem->type != QUOTE_D
				&& elem->type != REDIR_IN && elem->type != REDIR_OUT
				&& elem->type != REDIR_HD && elem->type != REDIR_AP)
			&& elem->next && elem->next->type != WSPACE)
			fusion_with_next_elem(elem, data);
		if (elem->type == ENV_VA && elem->next && elem->next->type == ENV_VA)
			fusion_env_va(elem, data);
		elem = elem->next;
	}
	return (0);
}
