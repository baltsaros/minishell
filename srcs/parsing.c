#include "../include/minishell.h"

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
				return (print_syntax_error_cmd(args->next));
			elem->pipe = 1;
		}
		args = args->next;
	}
	return (elem);
}

t_cmd	*init_elem(t_node *args, t_input *data)
{
	t_cmd	*elem;

	elem = init_empty_elem(data);
	if (!elem)
		return (NULL);
	elem = fill_elem(args, elem, data);
	if (!elem)
		return (NULL);
	return (elem);
}

t_cmd	*parse_cmd(t_input *data)
{
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;
	t_node	*tmp;

	tmp = data->args;
	while (tmp)
	{
		first_elem = init_elem(tmp, data);
		if (first_elem)
			break ;
		tmp = next_elem(tmp);
		if (!tmp || !tmp->next)
			break ;
	}
	if (!first_elem)
		return (NULL);
	arg = first_elem;
	tmp = next_elem(tmp);

	printf("Readed value: %s\n", tmp->value);

	if (!tmp)
		return (first_elem);
	while (tmp)
	{
		new_con = init_elem(tmp, data);
		if (!new_con)
		{
			tmp = next_elem(tmp);
			if (!tmp || !tmp->next)
				break ;
			continue ;
		}
		new_con->prev = arg;
		arg->next = new_con;
		arg = arg->next;
		tmp = next_elem(tmp);
		if (!tmp || !tmp->next)
			break ;
	}
	return (first_elem);
}

int	parsing(t_input *data)
{
	data->cmds = parse_cmd(data);
	if (!data->cmds)
		return (1);
	t_cmd	*tmp;
	tmp = data->cmds;
	while (tmp)
	{
		for (int i = 0; i != tmp->len_cmd; i++)
			printf("cmd[%d]: %s\n", i, tmp->cmd[i]);
		printf("len_cmd: %d\n", tmp->len_cmd);
		printf("delim: %s\n", tmp->delim);
		printf("in: %d\n", tmp->in);
		printf("in arg: %s\n", tmp->in_arg);
		printf("out: %d\n", tmp->out);
		printf("out arg: %s\n", tmp->out_arg);
		printf("pipe: %d\n", tmp->pipe);
		printf("[NEXT]\n");
		tmp = tmp->next;
	}
	return (0);
}
