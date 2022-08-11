/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:33 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 09:53:52 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_between_quote(t_node *args, int type)
{
	while (args->next && args->type != type)
		args = args->next;
	return (0);
}

int	get_braces_size(t_node	*elem, int type1, int type2)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (elem->value[i] != type1)
		i++;
	i++;
	while (elem->value[i] != type2)
	{
		size++;
		i++;
	}
	return (size);
}

char	*get_between_braces(t_node *elem, int type1, int type2)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = get_braces_size(elem, type1, type2);
	i = 0;
	j = 0;
	str = (char *) malloc ((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (elem->value[i] != type1)
		i++;
	i++;
	while (elem->value[i] != type2)
	{
		str[j] = elem->value[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

void	dollar_management(t_node *elem, t_input *data)
{
	char	*tmp;

	become_word_and_more(elem, data);
	if (elem->type == ENV_VA)
	{
		tmp = elem->value;
		elem->value = ms_strdup(ms_getenv(elem->value + 1, data), data);
		free(tmp);
	}
	else if (elem->type == ENV_VA_BR)
	{
		tmp = elem->value;
		elem->value = ms_strdup(
				ms_getenv(get_between_braces(
						elem, BRACES_L, BRACES_R), data), data);
		free(tmp);
	}
	else if (elem->type == ENV_P)
	{
		tmp = elem->value;
		elem->value = ms_strdup(get_between_braces(elem, BR_L, BR_R), data);
		free(tmp);
	}
	else if (elem->type == ENV_P_EM)
		empty_env_management(elem, data);
}

int	expanding_variables(t_node *elem, t_input *data)
{
	while (elem)
	{
		expansion_between_quote(elem);
		if (elem->type == DOLLAR)
			dollar_management(elem, data);
		else if (elem->type == DOLLAR_R && elem->flag != B_QUOTE)
		{
			elem->type = DOLLAR_VAR;
			free(elem->value);
			if (g_status > 255)
				g_status = (g_status >> 8) & 0xff;
			elem->value = ft_itoa(g_status);
			alloc_check_small(elem->value, data);
		}
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}
