/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:22:15 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 14:42:36 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_right_type(t_node *args)
{
	if (args->type == WORD || args->type == ASTER
		|| args->type == EXECUTABLE || args->type == ENV_VA
		|| args->type == ENV_VA_BR || args->type == ENV_P
		|| args->type == DOLLAR_VAR || args->type == SLASH
		|| args->type == EQUAL)
		return (0);
	return (1);
}

char	**init_cmd(t_node *args, t_input *data)
{
	int		size;
	int		i;
	char	**str;

	size = get_size_cmd(args);
	if (size == 0)
		return (NULL);
	i = 0;
	str = ms_malloc((size + 1) * sizeof(char *), data);
	while (args && args->type != PIPE)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			if (!is_a_right_type(args))
				str[i++] = ms_strdup(args->value, data);
			else if (args->type == EMPTY_ARG)
				str[i++] = ms_strdup("\0", data);
		}
		args = args->next;
	}
	str[i] = NULL;
	return (str);
}

t_cmd	*init_empty_elem(t_input *data)
{
	t_cmd	*elem;

	elem = ms_malloc(sizeof(t_cmd), data);
	elem->cmd = NULL;
	elem->len_cmd = 0;
	elem->delim = NULL;
	elem->in = 0;
	elem->in_arg = NULL;
	elem->out = 1;
	elem->out_arg = NULL;
	elem->pipe = -1;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_cmd	*fill_elem(t_node *args, t_cmd *elem, t_input *data)
{
	elem->cmd = init_cmd(args, data);
	if (!elem->cmd)
		return (NULL);
	elem->len_cmd = get_len_cmd(elem->cmd);
	while (args && args->type != PIPE)
	{
		if (redirection_check(args, elem, data) == 1)
		{
			ms_free_cmd(elem);
			return (NULL);
		}
		if (args->next && args->next->type == PIPE)
		{
			if (!args->next->next || is_the_next_is_right_type(args->next) == 1)
				return (print_syntax_error_cmd(args->next, data));
			elem->pipe = 1;
		}
		args = args->next;
	}
	return (elem);
}

t_cmd	*init_elem(t_node *args, t_input *data)
{
	t_cmd	*elem;
	t_cmd	*head;

	elem = init_empty_elem(data);
	if (!elem)
		return (NULL);
	head = elem;
	elem = fill_elem(args, elem, data);
	if (!elem)
	{
		ms_free_cmd(head);
		return (NULL);
	}
	return (elem);
}
