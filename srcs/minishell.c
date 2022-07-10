#include "../include/minishell.h"

int		read_after_pipe(char **buf, char *msg, char c)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ft_charjoin_free(*buf, '\n');
		*buf = ft_strjoin_free(*buf, tmp);
		if (!ft_strchr(tmp, c))
		{
			free(tmp);
			break;
		}
		free(tmp);
	}
	return (0);
}

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

int		check_field(char **buf, t_input *data)
{
	int		quote;
	int		quote_d;
	char	*tmp;

	data->i = 0;
	quote = 0;
	quote_d = 0;
	tmp = *buf;
	while (tmp[data->i])
	{
		if (tmp[data->i] == '\'')
			++quote;
		else if (tmp[data->i] == '\"')
			++quote_d;
		++data->i;
	}
	if (quote && quote % 2 != 0)
		read_after(buf, "quote>", '\'');
	else if (quote_d &&quote_d % 2 != 0)
		read_after(buf, "dquote>", '\"');
	if (tmp[data->i - 1] == '|')
		read_after_pipe(buf, ">", '|');
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

	if (!data->buf[*i + 1])
		return ;
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

void	check_dollar(t_input *data)
{
	int	i;

	i = 0;
	data->node_tmp = data->args;
	while (data->node_tmp->next && data->node_tmp->type != DOLLAR)
		data->node_tmp = data->node_tmp->next;
	while (data->buf[i] && data->buf[i] != '$')
		++i;
	if (data->node_tmp && data->node_tmp->next && data->node_tmp->type == DOLLAR)
	{
		if (data->buf[i + 1] && data->buf[i + 1] != ' ')
			data->node_tmp->next->type = DOLLAR;
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
	check_dollar(data);
}

void	copy_envp(t_input *data, char *envp[])
{
	int	size;

	size = 0;
	while(envp[size])
		++size;
	data->envp = (char **)malloc(sizeof(*data->envp) * (size + 1));
	alloc_check(data->envp);
	data->i = 0;
	while (envp[data->i])
	{
		data->envp[data->i] = envp[data->i];
		data->i++;
	}
	data->envp[data->i] = NULL;
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
	copy_envp(data, envp);
	data->envp_n = NULL;
	data->type = NULL;
	data->value = NULL;
	data->tmp = NULL;
	data->i = 0;
	data->j = 0;
	data->envp_tmp = NULL;
	data->node_tmp = NULL;
	data->builtins = builtins;
	create_envp(data, data->envp);
	//ft_envp_print(data->envp_n);
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

int	is_right_buf(char	*buf)
{
	int	i;

	i = 0;
	if (buf[0] == '\0')
		return (1);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
			&& buf[i] != '\v' && buf[i] != '\f' && buf[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

void	prompt(t_input *data)
{
	while (1)
	{
		data->buf = readline("minishell$ ");
		if (!data->buf)
			yo_exit(data);
		else if (is_right_buf(data->buf) != 1)
		{
			add_history(data->buf);
			check_field(&data->buf, data);
			data_init(data);
			if (parsing(data) == 0)
			{
				execute(data);
				ft_free_token(data->args);
				ft_free_cmd(data->cmds);
			}
			else
				ft_free_token(data->args);
		}
		//asterisks(&data);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input 			data;
	struct sigaction	act;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	if (sigaction(SIGINT, &act, NULL) == -1
		|| sigaction(SIGQUIT, &act, NULL) == -1)
		printf("[ERROR]: Signal handler failed\n");
	envp_init(&data, envp);
	prompt(&data);
	return ((data.status >> 8) & 0xff);
}
