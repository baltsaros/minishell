/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 10:25:59 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_envp_new(char *type, char *value, t_input *data)
{
	t_env	*node;

	node = ms_malloc(sizeof(t_env), data);
	node->type = type;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ms_envp_back(t_env **node, t_env *new)
{
	t_env	*tmp;

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

t_env	*ms_envp_del(t_env *node)
{
	t_env	*tmp;

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
	ms_free_node_elems(tmp);
	return (node);
}

void	ms_envp_print(t_env *node)
{
	int	i;

	if (!node)
	{
		printf("There are no envp nodes in the list\n");
		return ;
	}
	i = 0;
	printf("===== ENVP NODE =====\n");
	while (node)
	{
		printf("type for node[%d] is %s\n", i, node->type);
		printf("value for node[%d] is %s\n", i, node->value);
		node = node->next;
		++i;
	}
}

int	ms_envp_size(t_env *node)
{
	int	i;

	if (!node)
		return (0);
	i = 0;
	while (node->next)
	{
		++i;
		node = node->next;
	}
	return (i);
}
