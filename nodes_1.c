/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:10 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 10:25:56 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ms_token_new(int type, char *value, t_input *data)
{
	t_node	*node;

	node = ms_malloc(sizeof(t_node), data);
	node->type = type;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ms_token_back(t_node **node, t_node *new)
{
	t_node	*tmp;

	tmp = NULL;
	if (!node || !new)
		return ;
	if (!*node)
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

t_node	*ms_token_del(t_node *node)
{
	t_node	*tmp;

	if (!node)
		return (NULL);
	tmp = node;
	if (tmp->prev && tmp->next)
	{
		node = node->prev;
		node->next = tmp->next;
		node->next->prev = node;
	}
	else if (tmp->prev)
	{
		node = node->prev;
		node->next = NULL;
	}
	else if (tmp->next)
	{
		node = node->next;
		node->prev = NULL;
	}
	free(tmp->value);
	free(tmp);
	return (node);
}

void	ms_token_print(t_node *node)
{
	int	i;

	if (!node)
	{
		printf("There are no nodes in the list\n");
		return ;
	}
	i = 0;
	printf("===== NODE =====\n");
	while (node)
	{
		printf("type for node[%d] is %d\n", i, node->type);
		printf("value for node[%d] is %s\n", i, node->value);
		printf("flag for node[%d] is %d\n", i, node->flag);
		node = node->next;
		++i;
	}
}

int	ms_token_size(t_node *node)
{
	int	i;

	if (!node)
		return (0);
	i = 1;
	while (node->next)
	{
		++i;
		node = node->next;
	}
	return (i);
}
