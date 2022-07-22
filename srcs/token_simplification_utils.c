/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:30:33 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 13:42:29 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// receives token after quote and then goes until next toke with the same quote type
// and stops on it
int	is_between_quote(t_node *args, int type)
{
	while (args->next && args->type != type)
		args = args->next;
	// if (args && args->type == type)
	// 	args = args->next;
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
