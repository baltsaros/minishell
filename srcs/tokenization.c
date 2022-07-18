#include "../include/minishell.h"

void	create_token(t_input *data, char *str, int len, int type)
{
	data->value = ms_strndup(str, len, data);
	data->node_tmp = ms_token_new(type, data->value, data);
	ms_token_back(&data->args, data->node_tmp);
}

void	check_quotes(t_input *data, size_t *i, char c)
{
	data->k = *i;
	while (data->buf[*i] && data->buf[*i] != c)
	{
		if (data->buf[*i] == '$' && c == '\"')
			break ;
		++(*i);
	}
	if (*i != data->k)
		create_token(data, data->buf + data->k, *i - data->k, WORD);
	if (data->buf[*i] && data->buf[*i] == c)
	{
		create_token(data, data->buf + *i, 1, (int)c);
		++(*i);
	}
	else if (data->buf[*i] && data->buf[*i] == '$')
	{
		create_token(data, "$", 1, DOLLAR);
		++(*i);
		check_quotes(data, i, c);
	}
}

void	check_asterisk(t_input *data)
{
	t_node	*tmp;
	int		type;

	tmp = data->args;
	while (tmp)
	{
		if (tmp->type == QUOTE || tmp->type == QUOTE_D)
		{
			type = tmp->type;
			tmp = tmp->next;
			while (tmp->next && tmp->type != type)
				tmp = tmp->next;
		}
		if (ft_strchr(tmp->value, '*'))
			tmp->type = ASTER;
		tmp = tmp->next;
	}
}

void	check_dollar(t_input *data)
{
	t_node	*tmp;

	tmp = data->args;
	while (tmp)
	{
		while (tmp->next && tmp->type != DOLLAR)
			tmp = tmp->next;
		if (tmp && tmp->type == DOLLAR)
		{
			if (tmp->next && (tmp->next->type == WSPACE
					|| (tmp->next->type == QUOTE && tmp->value[0] != '$')))
				tmp->type = WORD;
			if (tmp->next && tmp->next->type != WSPACE
				&& tmp->next->type != QUOTE && tmp->next->type != QUOTE_D)
				tmp->next->type = DOLLAR;
		}
		tmp = tmp->next;
	}
}

void	check_next(t_input *data, size_t *i)
{
	int	type;
	int	next;

	type = check_charset(data->buf[*i], "\"$\'&<>=|/(){}");
	if (!data->buf[*i + 1])
		next = 0;
	else
		next = check_charset(data->buf[*i + 1], "<>|&");
	if (type == next)
	{
		data->value = ms_strndup(data->buf + *i, 2, data);
		type += 100;
		++(*i);
	}
	else
		data->value = ms_strndup(data->buf + *i, 1, data);
	data->node_tmp = ms_token_new(type, data->value, data);
	ms_token_back(&data->args, data->node_tmp);
	++(*i);
	// if (data->buf[*i - 1] == '\"' || data->buf[*i - 1] == '\'')
	// 	check_quotes(data, i, data->buf[*i - 1]);
}
