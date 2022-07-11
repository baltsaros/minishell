#include "../include/minishell.h"

static void	check_quotes(t_input *data, size_t *i, char c)
{
	size_t	start;
	int		type;

	start = *i;
	while (data->buf[*i] != c)
		++*i;
	if (*i != start)
	{
		type = WORD;
		data->value = ft_strndup(data->buf + start, *i - start);
		data->node_tmp = ft_token_new(type, data->value);
		ft_token_back(&data->args, data->node_tmp);
	}
	if (data->buf[*i] && data->buf[*i] == c)
	{
		type = c;
		data->value = ft_strndup(data->buf + start - 1, 1);
		data->node_tmp = ft_token_new(type, data->value);
		ft_token_back(&data->args, data->node_tmp);
		++*i;
	}
}

static void	check_asterisk(t_input *data)
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

static void	check_dollar(t_input *data)
{
	int	i;

	i = 0;
	data->node_tmp = data->args;
	while (data->node_tmp->next && data->node_tmp->type != DOLLAR)
		data->node_tmp = data->node_tmp->next;
	while (data->buf[i] && data->buf[i] != '$')
		++i;
	if (data->buf[i + 1] && data->buf[i + 1] == ' ')
	{
		data->node_tmp->type = WORD;
		return ;
	}
	if (data->node_tmp && data->node_tmp->next
		&& data->node_tmp->type == DOLLAR)
	{
		if (data->buf[i + 1] && data->buf[i + 1] != ' '
			&& data->buf[i + 1] != '\'')
			data->node_tmp->next->type = DOLLAR;
	}
}

static void	check_next(t_input *data, size_t *i)
{
	int	type;
	int	next;

	type = check_charset(data->buf[*i], "\"$\'&<>=*|(){}");
	if (!data->buf[*i + 1])
		next = 0;
	else
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
	if (data->buf[*i - 1] == '\"' || data->buf[*i - 1] == '\'')
		check_quotes(data, i, data->buf[*i - 1]);
}

void	create_token(t_input *data)
{
	size_t	i;
	size_t	start;
	int		type;

	i = 0;
	while (data->buf[i])
	{
		while (check_charset(data->buf[i], " \f\n\r\t\v"))
			++i;
		start = i;
		while (data->buf[i] && !check_charset(data->buf[i]
				, "\"$\'&<>=*| \f\n\r\t\v(){}"))
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
