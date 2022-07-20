#include "../include/minishell.h"

int	redirection_check(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->value && args->value[0] == '<')
	{
		if (!args->next || is_the_next_is_in_arg(args) == 1)
			return (print_syntax_error_bool(args));
		if (args->next && args->next->type == IN_ARG)
		{
			if (init_in(args, elem, data) == 1)
				return (1);
		}
		else if (args->next->next && args->next->next->type == IN_ARG)
		{
			args = args->next;
			if (init_in(args, elem, data) == 1)
				return (1);
		}
		else
			return (print_syntax_error_bool(args));
	}
	else if (args->value && args->value[0] == '>')
	{
		if (!args->next || is_the_next_is_out_arg(args) == 1)
			return (print_syntax_error_bool(args));
		if (args->next && args->next->type == OUT_ARG)
		{
			if (init_out(args, elem, data) == 1)
				return (1);
		}
		else if (args->next->next && args->next->next->type == OUT_ARG)
		{
			if (init_out(args, elem, data) == 1)
				return (1);
		}
		else
			return (print_syntax_error_bool(args));
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
		args = args->next;
		elem->delim = ms_strdup(args->value, data);
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			error_check(-1, "in signals ", 11, data);
		data->pid = fork();
		error_check(data->pid, "In fork ", 9, data);
		if (data->pid == 0)
			ms_heredoc(elem->delim, elem, data);
		elem->in_arg = ms_strdup("heredoc.tmp", data);
		waitpid(data->pid, &g_status, 0);
		if (WEXITSTATUS(g_status) == 130)
		{
			unlink("heredoc.tmp");
			return (1);
		}
		elem->in = open("heredoc.tmp", O_RDONLY);
		if (error_check_nofork(elem->in, "in parsing open ", 16, data))
			return (1);
		unlink("heredoc.tmp");
		return (0);
	}
	else if (args->type == REDIR_IN)
	{
		if (elem->in)
			close(elem->in);
		args = args->next;
		elem->in_arg = ms_strdup(args->value, data);
		elem->in = open(elem->in_arg, O_RDONLY);
		if (error_check_nofork(elem->in, "in parsing open ", 16, data))
			return (1);
		return (0);
	}
	return (1);
}

int	init_out(t_node *args, t_cmd *elem, t_input *data)
{
	if (args->type == REDIR_AP)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (error_check_nofork(elem->out, "in parsing open ", 16, data))
			return (1);
		return (0);
	}
	else if (args->type == REDIR_OUT)
	{
		args = args->next;
		elem->out_arg = ms_strdup(args->value, data);
		elem->out = open(elem->out_arg, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (error_check_nofork(elem->out, "in parsing open ", 16, data))
			return (1);
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
