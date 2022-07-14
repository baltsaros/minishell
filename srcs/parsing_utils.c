#include "../include/minishell.h"

int	redirection_check(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->value[0] == '<')
	{
		if (!args->next)
		//|| is_the_next_is_word(args) == 1)
			return (print_syntax_error_bool(args));
		if (init_in(args, elem, data) == 1)
			return (1);
	}
	else if (args->value[0] == '>')
	{
		if (!args->next) 
		//|| is_the_next_is_word(args) == 1)
			return (print_syntax_error_bool(args));
		if (init_out(args, elem, data) == 1)
			return (1);
	}
	return (0);
}

t_node	*next_elem(t_node *args)
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

int	init_in(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->type == REDIR_HD)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			printf("[ERROR]: SIGNAL HANDLER FAILED!\n");
		args = args->next;
		elem->delim = ms_strdup(args->value, data);
		ms_heredoc(elem->delim, elem, data);
		elem->in_arg = "heredoc.tmp";
		return (0);
	}
	else if (args->type == REDIR_IN)
	{
		args = args->next;
		elem->in_arg = ms_strdup(args->value, data);
		elem->in = open(elem->in_arg, O_RDONLY);
		return (0);
	}
	return (1);
}

int	init_out(t_node *args, t_cmd *elem, t_input *data)
{
	(void)data;
	if (args->type == REDIR_AP)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
		return (0);
	}
	else if (args->type == REDIR_OUT)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
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
