/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/23 11:46:29 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_end_elem(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (0);
	if (c == '\0' || c == '\n' || c == '&')
		return (0);
	return (1);
}

int	get_nb_elem(char	*buf)
{
	int count;
	int	i;

	count = 1;
	i = 0;
	while (buf[i])
	{
		if (!is_end_elem(buf[i]))
		{
			count++;
			while (!is_end_elem(buf[i]))
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	get_size_elem(char	*buf, int pos)
{
	int	i;
	
	i = 0;
	if (is_end_elem(buf[pos]))
	{
		while (buf[pos] && is_end_elem(buf[pos]))
		{
			pos++;
			i++;
		}
	}
	else
	{
		while (buf[pos] && !is_end_elem(buf[pos]))
		{
			pos++;
			i++;
		}
	}
	return (i);
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

int	parsing(t_input *data, char *buf)
{
	(void)data;
	t_node	*parsing;
	
	buf = remove_white_spaces(buf);
	parsing = get_args(buf, get_nb_elem(buf));
	while (parsing)
	{
		printf("parsed value: %s\n", parsing->value);
		parsing = parsing->next;
	}
	free(buf);
	return (0);
}