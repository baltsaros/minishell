#include "../include/minishell.h"

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

int	init_in(t_node *args, t_cmd *elem)
{
	if (args->type == REDIR_HD)
	{
		args =  args->next;
		elem->delim = ft_strdup(args->value);
		if (!elem->delim)
			return (1);
		ft_heredoc(elem->delim, elem);
		elem->in_arg = "heredoc.tmp";
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

int	get_len_cmd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
