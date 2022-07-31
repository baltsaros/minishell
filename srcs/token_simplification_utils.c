/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:33 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 14:25:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	elem = dollar_token_simplification(elem, data);
	if (elem->type == ENV_VA)
		elem->value = ms_strdup(ms_getenv(elem->value + 1, data), data);
	else if (elem->type == ENV_VA_BR)
		elem->value = ms_strdup(
				ms_getenv(get_between_braces(
						elem, BRACES_L, BRACES_R), data), data);
	else if (elem->type == ENV_P)
		elem->value = ms_strdup(get_between_braces(elem, BR_L, BR_R), data);
	else if (elem->type == ENV_P_EM)
	{
		elem->type = 0;
		free(elem->value);
		elem->value = ms_strdup(NULL, data);
	}
}

int	expanding_variables(t_node *elem, t_input *data)
{
	while (elem)
	{
		if (!is_between_p(elem))
			elem->type = WORD;
		if (elem->flag == B_QUOTE)
			elem->type = WORD;
		if (elem->type == DOLLAR)
			dollar_management(elem, data);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}
