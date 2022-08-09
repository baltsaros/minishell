/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_simplification.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:21:33 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/08 15:44:11 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_braces_2(t_node *elem, t_input *data)
{
	while (elem && elem->next && elem->next->type != BRACES_R)
	{
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	if (elem->next && elem->next->type == BRACES_R)
	{
		elem->type = ENV_VA_BR;
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	else
	{
		elem->type = WORD;
		while (elem && elem->next && elem->type != WSPACE)
		{
			elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
			ms_token_del(elem->next);
		}
	}
}

void	dollar_braces(t_node *elem, t_input *data)
{
	elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
	ms_token_del(elem->next);
	if (elem->next && elem->next->type == WORD)
		dollar_braces_2(elem, data);
	else if (elem->next && elem->next->type == BRACES_R)
	{
		elem->type = ENV_BR_EM;
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
}

void	dollar_p_2(t_node *elem, t_input *data)
{
	while (elem && elem->next && elem->next->type != BR_R)
	{
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	if (elem->next && elem->next->type == BR_R)
	{
		elem->type = ENV_P;
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	else
	{
		elem->type = WORD;
		while (elem && elem->next && elem->type != WSPACE)
		{
			elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
			ms_token_del(elem->next);
		}
	}
}

void	dollar_p(t_node *elem, t_input *data)
{
	elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
	ms_token_del(elem->next);
	if (elem->next && elem->next->type == WORD)
		dollar_p_2(elem, data);
	else if (elem->next && elem->next->type == BR_R)
	{
		elem->type = ENV_P_EM;
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
}

t_node	*dollar_token_simplification(t_node *elem, t_input *data)
{
	if (elem->next && elem->next->type == WORD)
	{
		elem->type = ENV_VA;
		elem->value = ms_strjoin_free(elem->value, elem->next->value, data);
		ms_token_del(elem->next);
		if (!ft_strncmp(elem->value, "$?", 3))
		{
			elem->type = DOLLAR_VAR;
			free(elem->value);
			if (g_status > 255)
				g_status = (g_status >> 8) & 0xff;
			elem->value = ft_itoa(g_status);
			alloc_check_small(elem->value, data);
		}
	}
	else if (elem->next && elem->next->type == BRACES_L)
		dollar_braces(elem, data);
	else if (elem->next && elem->next->type == BR_L)
		dollar_p(elem, data);
	return (elem);
}
