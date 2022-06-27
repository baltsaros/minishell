/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:44:17 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/27 03:12:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_type(char *str)
{
	if (is_end_elem(str[0]))
		return (WORD);
	return (0);
}

t_node	*init_elem(char	*buf, int pos)
{
	int	i;
	int size;
	t_node	*elem;

	i = 0;
	size = get_size_elem(buf, pos);
	elem = (t_node *) malloc (sizeof(t_node));
	if (!elem)
		return (NULL);
	elem->value = (char *) malloc ((size + 1) * sizeof(char));
	if (!elem->value)
		return (NULL);
	while (i != size)
	{
		elem->value[i] = buf[pos++];
		i++;
	}
	elem->value[i] = '\0';
	elem->type = init_type(elem->value);
	elem->i = size;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_node	*get_args(char *buf, int nb_elem)
{
	int		i;
	int		pos;
	t_node	*first_elem;
	t_node	*args;
	t_node	*new_con;

	i = 1;
	pos = 0;
	first_elem = init_elem(buf, 0);
	if (!first_elem)
		return (NULL);
	args = first_elem;
	while (i < nb_elem)
	{
		pos += args->i;
		new_con = init_elem(buf, pos);
		if (!new_con)
			return (NULL);
		new_con->prev = args;
		args->next = new_con;
		args = args->next;
		i++;
	}
	return (first_elem);
}