/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:38:20 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/07/03 17:25:51 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_args(t_node	*args)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (args->type == WORD && args)
	{
		if (args->value[0] != '-')
		{
			str = ft_strjoin_free(str, args->value);
            if (!str)
            {
                free(str);
                return (NULL);
            }
			str = ft_strjoin_free(str, " ");
			if (!str)
			{
				free(str);
				return (NULL);
			}
		}
		if (args->next)
			args = args->next;
		else
			break ;
	}
	return (str);
}
