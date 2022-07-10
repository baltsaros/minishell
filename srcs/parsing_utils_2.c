/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/10 23:36:14 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *str_variable(char  *str, t_node *args)
{
	char	*value;
	
	if (args->next)
	{
		args = args->next;
		value = getenv(args->value);
		if (!value)
			return (str);
		str = ft_strjoin_free(str, value);
		if (!str)
			return (NULL);
		str = ft_strjoin_free(str, " ");
		if (!str)
			return (NULL);
	}
	else
		return (NULL);
    return (str);
}

char	*str_other(char	*str, t_node *args)
{
	str = ft_strjoin_free(str, args->value);
	if (!str)
		return (NULL);
	args = args->next;
	str = ft_strjoin_free(str, args->value);
	if (!str)
		return (NULL);
	return (str);
}

char    *str_word(char *str, t_node *args)
{
    str = ft_strjoin_free(str, args->value);
	if (!str)
        return (NULL);
	str = ft_strjoin_free(str, " ");
	if (!str)
		return (NULL);
    return (str);
}

char	*get_args(t_node	*args)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (args && (args->type == WORD || args->type == DOLLAR || args->type == QUOTE_D || args->type == EQUAL))
	{
		if (args->type == DOLLAR && !ft_strncmp(args->next->value, "?", 2))
		{
			str = str_other(str, args);
			if (!str)
				return (NULL);
			args = args->next;
		}
		else if (args->type == DOLLAR && (args->next && args->next->type == DOLLAR))
		{
            str = str_variable(str, args);
            if (!str)
                return (NULL);
			args = args->next;
		}
		else if (args->type != QUOTE_D)
		{
			str = str_word(str, args);
            if (!str)
                return (NULL);
		}
		if (args->next)
			args = args->next;
		else
			break ;
	}
	return (str);
}

int	redirection_check(t_node *args, t_cmd *elem)
{
	if (args->value[0] == '<')
	{
		if (!args->next || is_the_next_is_word(args) == 1)
			return (print_syntax_error_bool(args));
		if (init_in(args, elem) == 1)
			return (1);
	}
	else if (args->value[0] == '>')
	{
		if (!args->next || is_the_next_is_word(args) == 1)
			return (print_syntax_error_bool(args));
		if (init_out(args, elem) == 1)
			return (1);
	}
	return (0);
}