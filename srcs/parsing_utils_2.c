/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/14 14:53:02 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_between_d_quote(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == QUOTE_D)
		return (1);
	while (args->prev && args->type != QUOTE_D && args->type != PIPE)
		args = args->prev;
	if (args->type == QUOTE_D)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != QUOTE_D && args->type != PIPE)
		args = args->next;
	if (args && args->type == QUOTE_D)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

int	get_size_cmd(t_node	*args)
{
	int	i;

	i = 0;
	while (args && args->type != PIPE)
	{
		if (args->type == ASTER)
			i++;
		else if (args->type == DOLLAR
			&& (args->next && args->next->type == WORD))
		{
			if ((args->prev && args->prev->type != WORD)
				&& (args->prev->prev && args->prev->prev->type != DOLLAR))
			{
				i++;
				args = args->next;
			}
			else if (!args->prev || !args->prev->prev)
			{
				i++;
				args = args->next;
			}
		}
		else if (args->type == WORD)
		{
			if (args->prev && args->prev->type != DOLLAR)
				i++;
			else if (!args->prev)
				i++;
		}
		else if (args->type == AND
			|| args->type == OR || args->type == EQUAL)
			i++;
		else if (args->type == DOLLAR
			&& ((args->next && args->next->type != QUOTE) || !args->next))
			i++;
		if (!is_between_d_quote(args) && args && ((args->prev && args->prev->type == QUOTE_D) || (args->next && args->next->type == QUOTE_D)))
		{
			if (args->prev && is_between_d_quote(args->prev) && (args->prev->prev && is_between_d_quote(args->prev->prev) && (args->prev->prev->type == WORD
		 	|| args->prev->prev->type == AND || args->prev->prev->type == OR 
			|| args->prev->prev->type == EQUAL)))
			 	i--;
			if (args->next && is_between_d_quote(args->next) && (args->next->next && is_between_d_quote(args->next->next) && (args->next->next->type == WORD
			|| args->next->next->type == AND || args->next->next->type == OR 
			|| args->next->next->type == EQUAL)))
				i--;
		}
		
		if (args && !is_between_d_quote(args))
		{
		 	if (args->prev && args->prev->type == WORD)
				i--;
		}
		args = args->next;
	}
	// printf("I: %d\n", i);
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

char	*init_aster_word(t_node	*args, char *str)
{
	if (args->prev && args->prev->type == WORD_AST)
	{
		str = ft_strjoin_free(str, args->prev->value);
		if (!str)
			return (NULL);
	}
	str = ft_strjoin_free(str, args->value);
	if (!str)
		return (NULL);
	if (args->next && args->next->type == WORD_AST)
	{
		args = args->next;
		str = ft_strjoin_free(str, args->value);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	**init_cmd(t_node *args, t_input *data)
{
	int		size;
	int		i;
	char	**str;
	
	size = get_size_cmd(args);
	i = 0;
	str = ms_malloc((size + 1) * sizeof(char *), data);
	while (args && i != size && args->type != PIPE)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			str[i] = ms_strdup("", data);
			if (args->type == ASTER)
			{
				str[i] = init_aster_word(args, str[i]);
				if (!str[i])
					return (NULL);
				i++;
			}
			if (args->type == WORD && (args->next && args->next->type == QUOTE_D))
			{
				str[i] = ft_strjoin_free(str[i], args->value);
				if (!str[i])
					return (NULL);
				args = args->next;
				if (args->next)
				{
					args = args->next;
					while (args && args->type != QUOTE_D)
					{
						str[i] = ft_strjoin_free(str[i], args->value);
						if (!str[i])
							return (NULL);
						args = args->next;
					}
					if (args->type == QUOTE_D && args->next)
					{
						args = args->next;
						str[i] = ft_strjoin_free(str[i], args->value);
						if (!str[i])
							return (NULL);
					}
					i++;
				}
				else
					i++;
			}
			// else if ()
			// {
			// 	str[i] = ft_strjoin_free(str[i], args->value);
			// 	if (!str[i])
			// 		return (NULL);
			// 	i++;
			// }
			// else if (args->type == DOLLAR
			// 	&& (args->next && args->next->type == WORD))
			// {
			// 	if (!ft_strncmp(args->next->value, "?", 2))
			// 	{
			// 		str[i] = ft_strjoin_free(str[i], args->value);
			// 		if (!str[i])
			// 			return (NULL);
			// 		args = args->next;
			// 		str[i] = ft_strjoin_free(str[i], args->value);
			// 		if (!str[i])
			// 			return (NULL); 
			// 	}
			// 	else
			// 	{
			// 		args = args->next;
			// 		str[i] = get_env_variable(args->value);
			// 	}
			// 	i++;
			// }
			// else if (args->type == DOLLAR
			// 	&& ((args->next && args->next->type != QUOTE) || !args->next))
			// {
			// 	str[i] = ft_strjoin_free(str[i], args->value);
			// 	if (!str[i])
			// 		return (NULL);
			// 	i++;
			// }
			else
				free(str[i]);
		}
		args = args->next;
	}
	str[i] = NULL;
	return (str);
}
