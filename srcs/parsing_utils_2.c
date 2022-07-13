/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/13 22:53:49 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_size_cmd(t_node	*args)
{
	int	i;

	i = 0;
	while (args)
	{
		if (args->type == ASTER)
			i++;
		else if ((args->type == WORD && (args->prev && args->prev->type != DOLLAR))
			|| (args->type == WORD || args->type == AND
			|| args->type == OR || args->type == EQUAL))
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
		if ((args->prev && args->prev->type == QUOTE_D) && (args->next && args->next->type == QUOTE_D))
		{
			if (args->prev->prev && (args->prev->prev->type == WORD
		 		|| args->prev->prev->type == AND || args->prev->prev->type == OR 
				|| args->prev->prev->type == EQUAL))
		 		i--;
			if (args->next->next && (args->next->next->type == WORD
				|| args->next->next->type == AND || args->next->next->type == OR 
				|| args->next->next->type == EQUAL))
				i--;
		}
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
			str[i] = ft_strdup("");
			if (!str[i])
				return (NULL);
			if (args->type == ASTER)
			{
				if (!str[i])
					return (NULL);
				if (args->prev && args->prev->type == WORD_AST)
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
			else if ((args->type == WORD && (args->prev && args->prev->type != DOLLAR))
				|| ((args->type == WORD || args->type == AND || args->type == OR 
				|| args->type == EQUAL) 
				&& ((args->prev && args->prev->type == QUOTE_D)
				&& (args->next && args->next->type == QUOTE_D))))
			{
				if (args->prev && args->prev->type == QUOTE_D)
				{
					if (args->prev->prev && (args->prev->prev->type == WORD
						|| args->prev->prev->type == AND || args->prev->prev->type == OR 
						|| args->prev->prev->type == EQUAL))
					{
						str[i] = ft_strjoin_free(str[i], args->prev->prev->value);
						if (!str[i])
							return (NULL);
					}
				}
				str[i] = ft_strjoin_free(str[i], args->value);
				if (!str[i])
					return (NULL);
				if (args->next && args->next->type == QUOTE_D)
				{
					if (args->next->next && (args->next->next->type == WORD
						|| args->next->next->type == AND || args->next->next->type == OR 
						|| args->next->next->type == EQUAL))
					{
						args = args->next;
						str[i] = ft_strjoin_free(str[i], args->next->value);
						if (!str[i])
							return (NULL);
					}
				}
				i++;
			}
			else if ((args->type == WORD && (args->prev && args->prev->type != DOLLAR))
				|| ((args->type == WORD || args->type == AND || args->type == OR 
				|| args->type == EQUAL) 
				&& ((!args->prev || args->prev->type != QUOTE_D) && (!args->next || args->next->type != QUOTE_D))))
			{
				str[i] = ft_strjoin_free(str[i], args->value);
				if (!str[i])
					return (NULL);
				i++;
			}
			else if (args->type == DOLLAR
				&& (args->next && args->next->type == DOLLAR))
			{
				args = args->next;
				str[i] = get_env_variable(args->value);
				i++;
			}
			else if (args->type == DOLLAR
				&& ((args->next && args->next->type != QUOTE) || !args->next))
			{
				str[i] = ft_strjoin_free(str[i], args->value);
				if (!str[i])
					return (NULL);
				i++;
			}
			else
				free(str[i]);
		}
		if (args->next)
			args = args->next;
	}
	str[i] = NULL;
	return (str);
}
