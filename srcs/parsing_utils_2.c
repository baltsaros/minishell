/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/12 16:55:47 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_right_type(t_node *args)
{
	if (args->type == WORD
		|| args->type == DOLLAR || args->type == EQUAL 
		|| args->type == QUOTE_D || args->type == QUOTE
		|| args->type == WORD_AST || args->type == ASTER
		|| args->type == WORD_AST_B || args->type == OR
		|| args->type == AND)
		return (0);
	return (1);
}

int	get_size_cmd(t_node	*args)
{
	int	i;

	i = 0;
	while (args)
	{
		if (args->type == ASTER)
			i++;
		else if (args->type == DOLLAR
			&& (args->next && args->next->type == DOLLAR))
		{
			i++;
			args = args->next;
		}
		else if (args->type == DOLLAR
			&& ((args->next && args->next->type != QUOTE) || !args->next))
			i++;
		else if (args->type == WORD && args->prev)
		{
			if (args->prev->type != REDIR_AP && args->prev->type != REDIR_HD)
				i++;
		}
		else if (args->type == WORD)
			i++;
		args = args->next;
	}

	printf("I: %d\n", i);

	return (i);
}

char	*get_env_variable(char *arg)
{
	char	*str;

	str = getenv(arg);
	if (!str)
		return (NULL);
	return (str);
}

char	**init_cmd(t_node	*args)
{
	int		size;
	int		i;
	char	**str;
	
	size = get_size_cmd(args);
	i = 0;
	str = (char	**) malloc ((size + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (args && i != size)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			if (args->type == ASTER)
			{
				str[i] = ft_strdup("");
				if (!str[i])
					return (NULL);
				if (args->prev && args->prev->type == WORD_AST_B)
				{
					str[i] = ft_strjoin_free(str[i], args->prev->value);
					if (!str[i])
						return (NULL);
				}
				str[i] = ft_strjoin_free(str[i], args->value);
				if (!str[i])
					return (NULL);
				if (args->next && args->next->type == WORD_AST)
				{
					args = args->next;
					str[i] = ft_strjoin_free(str[i], args->value);
					if (!str[i])
						return (NULL);
				}
				i++;
			}
			else if (args->type == DOLLAR && (args->next && args->next->type == DOLLAR))
			{
				if (!ft_strncmp(args->next->value, "?", 2))
				{
					str[i] = ft_strdup("");
					if (!str[i])
						return (NULL);
					str[i] = ft_strjoin_free(str[i], args->value);
					if (!str[i])
						return (NULL);
					args = args->next;
					str[i] = ft_strjoin_free(str[i], args->value);
					if (!str[i])
						return (NULL);
					i++;
				}
				else
				{
					args = args->next;
					str[i] = get_env_variable(args->value);
					i++;
				}
			}
			else if (args->type == DOLLAR && ((args->next && args->next->type != QUOTE) || !args->next))
			{
				str[i] = ft_strdup(args->value);
				if (!str[i])
					return (NULL);
				i++;
			}
			else if (args->type == WORD && args->prev)
			{
				if (args->prev->type != REDIR_AP && args->prev->type != REDIR_HD)
				{
					str[i] = ft_strdup(args->value);
					if (!str[i])
						return (NULL);
					i++;
				}
			}
			else if (args->type == WORD)
			{
				str[i] = ft_strdup(args->value);
				if (!str[i])
					return (NULL);
				i++;
			}
		}
		args = args->next;
	}
	str[i] = NULL;
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
