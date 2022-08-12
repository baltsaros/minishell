/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:34 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/10 15:47:48 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_input *data, char *str, int len, int type)
{
	data->value = ms_strndup(str, len, data);
	data->node_tmp = ms_token_new(type, data->value, data);
	ms_token_back(&data->args, data->node_tmp);
}

// add every found file into a separate linked list
static void	split_aster(t_input *data, t_node *ast)
{
	char	**spl;
	int		i;

	spl = ft_split(ast->value, ' ');
	alloc_check_big(spl, data);
	free(ast->value);
	ast->value = ms_strdup(spl[0], data);
	data->value = ms_strdup(" ", data);
	data->node_tmp = ms_token_new(WSPACE, data->value, data);
	ms_token_back(&data->args, data->node_tmp);
	i = 1;
	while (spl[i])
	{
		data->value = ms_strdup(spl[i], data);
		data->node_tmp = ms_token_new(ASTER, data->value, data);
		ms_token_back(&data->args, data->node_tmp);
		data->value = ms_strdup(" ", data);
		data->node_tmp = ms_token_new(WSPACE, data->value, data);
		ms_token_back(&data->args, data->node_tmp);
		++i;
	}
	ms_free(spl);
}

// find unquoted asterisks and change token type
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
		{
			tmp->type = ASTER;
			asterisks(data, tmp);
			split_aster(data, tmp);
		}
		tmp = tmp->next;
	}
}

// check for the second quote or character
void	check_next(t_input *data, size_t *i)
{
	int	type;
	int	next;

	type = check_charset(data->buf[*i], "\"$\'&<>=|/(){}");
	if (!data->buf[*i + 1])
		next = 0;
	else
		next = check_charset(data->buf[*i + 1], "?<>|&");
	if (type == next)
	{
		data->value = ms_strndup(data->buf + *i, 2, data);
		type += 100;
		++(*i);
	}
	else
		data->value = ms_strndup(data->buf + *i, 1, data);
	if (type == '$' && next == '?')
	{
		type = DOLLAR_R;
		++(*i);
	}
	data->node_tmp = ms_token_new(type, data->value, data);
	ms_token_back(&data->args, data->node_tmp);
	++(*i);
}

// white space is also considered as a token
void	tokenization(t_input *data)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (check_charset(data->buf[i], " \f\n\r\t\v"))
		++i;
	while (data->buf[i])
	{
		start = i;
		while (check_charset(data->buf[i], " \f\n\r\t\v"))
			++i;
		if (i != start)
			create_token(data, data->buf + start, i - start, WSPACE);
		start = i;
		while (data->buf[i] && !check_charset(data->buf[i]
				, "\"$\'&<>=| \f\n\r\t\v(){}/"))
			++i;
		if (i != start)
			create_token(data, data->buf + start, i - start, WORD);
		if (check_charset(data->buf[i], "\"$\'&<>=|(){}/"))
			check_next(data, &i);
	}
	check_asterisk(data);
}
