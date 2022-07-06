/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/06 15:27:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *str_other(char  *str, t_node *args)
{
	if (args->next)
	{
		args = args->next;
		if (args->type == WORD)
		{
			str = ft_strjoin_free(str, getenv(args->value));
			if (!str)
				return (NULL);
			str = ft_strjoin_free(str, " ");
			if (!str)
				return (NULL);
		}
	}
	else
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
	while (args && (args->type == WORD || args->type == DOLLAR || args->type == QUOTE_D))
	{
		if (args->type == DOLLAR)
		{
            str = str_other(str, args);
            if (!str)
                return (NULL);
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