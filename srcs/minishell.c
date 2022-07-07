#include "../include/minishell.h"

int		read_after(char **buf, char *msg, char c)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ft_charjoin_free(*buf, '\n');
		*buf = ft_strjoin_free(*buf, tmp);
		if (ft_strchr(tmp, c))
		{
			free(tmp);
			break;
		}
		free(tmp);
	}
	return (0);
}

int		check_field(char **buf)
{
	int		i;
	int		quote;
	int		quote_d;
	char	*tmp;

	if (!*buf)
		return (0);
	i = 0;
	quote = 0;
	quote_d = 0;
	tmp = *buf;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			++quote;
		else if (tmp[i] == '\"')
			++quote_d;
		++i;
	}
	if (quote && quote % 2 != 0)
		read_after(buf, "quote>", '\'');
	else if (quote_d &&quote_d % 2 != 0)
		read_after(buf, "dquote>", '\"');
	return (0);
}

void	create_envp(t_input *data, char *envp[])
{
	int		i;
	int		start;
	int		end;

	i = 0;
	while (envp[i])
	{
		start = 0;
		end = 0;
		while (envp[i][start] != '=')
			++start;
		while (envp[i][end])
			++end;
		data->type = ft_strndup(envp[i], start);
		data->value = ft_strndup(envp[i] + start + 1, end - start - 1);
		data->envp_tmp = ft_envp_new(data->type, data->value);
		ft_envp_back(&data->envp_n, data->envp_tmp);
		++i;
	}
}

void	check_next(t_input *data, size_t *i)
{
	int	type;
	int	next;

	type = check_charset(data->buf[*i], "\"$\'&<>=*|(){}");
	next = check_charset(data->buf[*i + 1], "<>|&");
	if (type == next)
	{
		data->value = ft_strndup(data->buf + *i, 2);
		type += 100;
		++*i;
	}
	else
		data->value = ft_strndup(data->buf + *i, 1);
	data->node_tmp = ft_token_new(type, data->value);
	ft_token_back(&data->args, data->node_tmp);
	++*i;
}

void	check_asterisk(t_input *data)
{
	int	i;

	i = 0;
	data->node_tmp = data->args;
	while (data->node_tmp->next && data->node_tmp->type != ASTER)
		data->node_tmp = data->node_tmp->next;
	while (data->buf[i] && data->buf[i] != '*')
		++i;
	if (data->node_tmp->type == ASTER)
	{
		if (data->buf[i - 1] && data->buf[i - 1] != ' ')
			data->node_tmp->prev->type = WORD_AST;
		if (data->buf[i + 1] && data->buf[i + 1] != ' ')
			data->node_tmp->next->type = WORD_AST;
	}
}

void	create_token(t_input *data)
{
	size_t	i;
	size_t	start;
	int		type;

	i = 0;
	start = 0;
	while (data->buf[i])
	{
		while (check_charset(data->buf[i], " \f\n\r\t\v"))
			++i;
		start = i;
		while (data->buf[i] && !check_charset(data->buf[i], "\"$\'&<>=*| \f\n\r\t\v(){}"))
			++i;
		if (i != start)
		{
			type = WORD;
			data->value = ft_strndup(data->buf + start, i - start);
			data->node_tmp = ft_token_new(type, data->value);
			ft_token_back(&data->args, data->node_tmp);
		}
		if (check_charset(data->buf[i], "\"$\'&<>=*|(){}"))
			check_next(data, &i);
	}
	check_asterisk(data);
}

void	envp_init(t_input *data, char *envp[])
{
	static struct builtin builtins[] =
	{
		{"pwd", &yo_pwd},
		{"cd", &yo_cd},
		{"echo", &yo_echo},
		{"export", &yo_export},
		{"env", &yo_env},
		{"unset", &yo_unset},
		{"exit", &yo_exit}
	};
	data->envp = envp;
	data->envp_n = NULL;
	data->type = NULL;
	data->value = NULL;
	data->tmp = NULL;
	data->i = 0;
	data->j = 0;
	data->envp_tmp = NULL;
	data->node_tmp = NULL;
	data->builtins = builtins;
	create_envp(data, envp);
	ft_envp_print(data->envp_n);
}

void	data_init(t_input *data)
{
	t_node *tmp;
	int		i;

	if (!data->buf || !*data->buf)
		return ;
	i = 0;
	data->status = 0;
	data->in = 0;
	data->out = 1;
	data->args = NULL;
	data->wild = NULL;
	create_token(data);
	tmp = data->args;
	data->argc = ft_token_size(data->args);
	data->argv = malloc(sizeof(data->argv) * (data->argc + 1));
	while (tmp)
	{
		data->argv[i] = tmp->value;
		tmp = tmp->next;
		++i;
	}
	data->argv[i] = NULL;
	// ft_token_print(data->args);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input data;
	struct sigaction act;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	envp_init(&data, envp);
	while (1)
	{
		data.buf = readline("yo> ");
		if (data.buf)
			add_history(data.buf);
		check_field(&data.buf);
		data_init(&data);
		//asterisks(&data);
		if (parsing(&data) == 0)
		{
			execute(&data);
			// ft_free_token(data.args);
			// ft_free_cmd(data.cmds);
		}
		// else
			// ft_free_token(data.args);
		// execute(&data);
	}
	return ((data.status >> 8) & 0xff);
}
