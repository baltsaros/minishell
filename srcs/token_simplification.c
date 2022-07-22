/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simplification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:32:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/22 13:55:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ms_getenv(char *var, t_input *data)
{
	t_env	*tmp;
	char	*str;

	tmp = data->envp_n;
	while (tmp && ft_strcmp(tmp->type, var))
		tmp = tmp->next;
	if (tmp)
		str = tmp->value;
	else
		return (NULL);
	return (str);
}

void	out_arg_management(t_node *elem)
{
	if (elem->next && (elem->next && elem->next->type == WSPACE))
	{
		elem = elem->next;
		if (elem->next && (elem->next->type != PIPE
				&& elem->next->type != REDIR_IN
				&& elem->next->type != REDIR_OUT
				&& elem->next->type != REDIR_HD
				&& elem->next->type != REDIR_AP))
			elem->next->type = OUT_ARG;
	}
	else if (elem->next && (elem->next->type != PIPE
			&& elem->next->type != REDIR_IN
			&& elem->next->type != REDIR_OUT
			&& elem->next->type != REDIR_HD
			&& elem->next->type != REDIR_AP))
		elem->next->type = OUT_ARG;
}

void	in_arg_management(t_node *elem)
{
	if (elem->next && (elem->next && elem->next->type == WSPACE))
	{
		elem = elem->next;
		if (elem->next && (elem->next->type != PIPE
				&& elem->next->type != REDIR_IN
				&& elem->next->type != REDIR_OUT
				&& elem->next->type != REDIR_HD
				&& elem->next->type != REDIR_AP))
			elem->next->type = IN_ARG;
	}
	else if (elem->next && (elem->next->type != PIPE
			&& elem->next->type != REDIR_IN
			&& elem->next->type != REDIR_OUT
			&& elem->next->type != REDIR_HD
			&& elem->next->type != REDIR_AP))
		elem->next->type = IN_ARG;
}

int	is_between_p(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == BR_L || args->type == BR_R)
		return (1);
	while (args->prev && args->type != BR_L && args->type != PIPE)
		args = args->prev;
	if (args->type == BR_L)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != BR_R && args->type != PIPE)
		args = args->next;
	if (args && args->type == BR_R)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

int	general_simplification(t_node *elem)
{
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == WORD && !ft_strncmp(elem->value, "./", 2))
			elem->type = EXECUTABLE;
		else if (elem->type == REDIR_OUT || elem->type == REDIR_AP)
			out_arg_management(elem);
		else if (elem->type == REDIR_IN || elem->type == REDIR_HD)
			in_arg_management(elem);
		elem = elem->next;
	}
	return (0);
}

int	empty_when_only_quote(t_node	*elem)
{
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->type == QUOTE_D && elem->next && elem->next->type == QUOTE_D)
		{
			elem->type = EMPTY_ARG;
			ms_token_del(elem->next);
		}
		if (elem->type == QUOTE && elem->next && elem->next->type == QUOTE)
		{
			elem->type = EMPTY_ARG;
			ms_token_del(elem->next);
		}
		elem = elem->next;
	}
	return (0);
}

void	dollar_management(t_node *elem, t_input *data)
{
	elem = dollar_token_simplification(elem, data);
	if (elem->type == ENV_VA)
		elem->value = ms_strdup(ms_getenv(elem->value + 1, data), data);
	else if (elem->type == ENV_VA_BR)
		elem->value = ms_strdup(
			ms_getenv(get_between_braces(elem, BRACES_L, BRACES_R), data), data);
	else if (elem->type == ENV_P)
		elem->value = ms_strdup(get_between_braces(elem, BR_L, BR_R), data);
	else if (elem->type == ENV_P_EM)
	{
		elem->type = 0;
		free(elem->value);
		elem->value = ms_strdup(NULL, data);
	}
}

int	expanding_variables(t_node *elem, t_input *data)
{
	while (elem)
	{
		if (!is_between_p(elem))
			elem->type = WORD;
		if (elem->type == DOLLAR)
			dollar_management(elem, data);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}

int	token_simplification(t_input *data)
{
	t_node	*elem;

    elem = data->args;
	printf("1 before everything: ");
	ms_token_print(data->args);
	if (expanding_variables(elem, data) == 1)
		return (1);
	printf("2 expanding variables: ");
	ms_token_print(data->args);
	if (word_total_fusion(elem, data) == 1)
 		return (1);
	printf("3 word total fusion: ");
	ms_token_print(data->args);
	if (quote_transformation(elem, data) == 1)
		return (1);
	printf("4 quote transformation: ");
	ms_token_print(data->args);
    if (general_simplification(elem) == 1)
		return (1);
	printf("5 general simplification: ");
	ms_token_print(data->args);
	
	// if (delete_useless_wspace(elem, data) == 1)
	// 	return (1);
	// printf("6 after delete useless wspace: ");
    // ms_token_print(data->args);
	// if (empty_when_only_quote(elem) == 1)
	// 	return (1);
	// printf("7 after empty when only quote: ");
	// ms_token_print(data->args);
    return (0);
}
