/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:38:20 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/07/06 15:11:41 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_args(t_node	*args)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (args && (args->type == WORD || args->type == DOLLAR))
	{
		if (args->type == DOLLAR)
		{
			if (args->next)
			{
				args = args->next;
				if (args->type == WORD)
				{
					str = ft_strjoin_free(str, getenv(args->value));
					if (!str)
						return (NULL);
				}
			}
			else
				return (NULL);
		}
		else
		{
			str = ft_strjoin_free(str, args->value);
			if (!str)
            	return (NULL);
		}
		str = ft_strjoin_free(str, " ");
		if (!str)
			return (NULL);
		if (args->next)
			args = args->next;
		else
			break ;
	}
	return (str);
}

t_node *next_elem(t_node *args)
{
	t_node	*next_elem;

	next_elem = args;
	while (next_elem)
	{
		if (!next_elem->next)
			break ;
		next_elem = next_elem->next;
		if (next_elem->prev && next_elem->prev->type == PIPE)
			break ;
	}
	return (next_elem);
}

t_cmd	*init_empty_elem(void)
{
	t_cmd	*elem;

	elem = (t_cmd *) malloc (sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->argument_buf = NULL;
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

int	init_in(t_node *args, t_cmd *elem)
{
	if (args->type == REDIR_HD)
	{
		args =  args->next;
		elem->delim = ft_strdup(args->value);
		if (!elem->delim)
			return (1);
		// Open heredoc here
		return (0);
	}
	else if (args->type == REDIR_IN)
	{
		args = args->next;
		elem->in_arg = ft_strdup(args->value);
		if (!elem->in_arg)
			return (1);
		elem->in = open(elem->in_arg, O_RDONLY);
		return (0);
	}
	return (1);
}

int	init_out(t_node *args, t_cmd *elem)
{
	if (args->type == REDIR_AP)
	{
		args = args->next;
		elem->out_arg = ft_strdup(args->value);
		if (!elem->out_arg)
			return (1);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
		return (0);
	}
	else if (args->type == REDIR_OUT)
	{
		args = args->next;
		elem->out_arg = ft_strdup(args->value);
		if (!elem->out_arg)
			return (1);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		return (0);
	}
	return (1);
}
