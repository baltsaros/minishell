#include "../include/minishell.h"

t_cmd	*fill_elem(t_node	*args, t_cmd *elem)
{
	elem->cmd = init_cmd(args);
	if (!elem->cmd)
		return (NULL);
	elem->len_cmd = get_len_cmd(elem->cmd);
	while (args && args->type != PIPE)
	{
	 	if (redirection_check(args, elem) == 1)
	 		return (NULL);
	 	if (args->next && args->next->type == PIPE)
	 	{
	 		if (!args->next->next || is_the_next_is_word(args->next) == 1)
	 			return (print_syntax_error_cmd(args->next));
	 		elem->pipe = 1;
	 	}
	 	args = args->next;
	}
	return (elem);
}

t_cmd	*init_elem(t_node *args)
{
	t_cmd	*elem;

	elem = init_empty_elem();
	if (!elem)
		return (NULL);
	elem = fill_elem(args, elem);
	if (!elem)
		return (NULL);
	return (elem);
}

t_cmd	*parse_cmd(t_input *data)
{
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;

	first_elem = init_elem(data->args);
	if (!first_elem)
		return (NULL);
	arg = first_elem;
	while (data->args)
	{
		data->args = next_elem(data->args);
		if (!data->args || !data->args->next)
			break ;
		new_con = init_elem(data->args);
		if (!new_con)
			return (NULL);
		new_con->prev = arg;
		arg->next = new_con;
		arg = arg->next;
	}
	return (first_elem);
}

int	parsing(t_input *data)
{
	data->cmds = parse_cmd(data);
	if (!data->cmds)
		return (1);
	// while (data->cmds)
	// {
	// 	for (int i = 0; data->cmds->cmd[i]; i++)
	// 		printf("cmd[%d]: %s\n", i, data->cmds->cmd[i]);
	// 	printf("len_cmd: %d\n", data->cmds->len_cmd);
	// 	printf("delim: %s\n", data->cmds->delim);
	// 	printf("in: %d\n", data->cmds->in);
	// 	printf("in arg: %s\n", data->cmds->in_arg);
	// 	printf("out: %d\n", data->cmds->out);
	// 	printf("out arg: %s\n", data->cmds->out_arg);
	// 	printf("pipe: %d\n", data->cmds->pipe);
	// 	printf("[NEXT]\n");
	// 	data->cmds = data->cmds->next;
	// }
	return (0);
}
