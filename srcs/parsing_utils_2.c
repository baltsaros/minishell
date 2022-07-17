/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:57 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/17 12:58:15 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_size_cmd(t_node	*args)
{
	int	i;

	i = 0;
	while (args && args->type != PIPE)
	{
		if (args->type != WSPACE && args->type != QUOTE && args->type != QUOTE_D)
		{
			if (!is_between_d_quote(args) || !is_between_quote(args))
			{
				if (args->prev && (args->prev->type == QUOTE || args->prev->type == QUOTE_D))
					i++;
			}
			else
				i++;
		}
		if (args->type == ENV_VA && args->prev && args->prev->type == ENV_VA)
			i--;
		if (args->type == IN_ARG || args->type == OUT_ARG)
			i--;
		if (!args->value || args->type == DOLLAR)
            i--;
		args = args->next;
	}
	printf("I: %d\n", i);
	return (i);
}

char	**init_cmd(t_node *args, t_input *data)
{
	int		size;
	int		i;
	char	**str;
	
	size = get_size_cmd(args);
	i = 0;
	str = ms_malloc((size + 1) * sizeof(char *), data);
	while (args && args->type != PIPE)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			str[i] = ms_strdup("", data);
			if (args->type == WORD || args->type == ASTER_WORD
				|| args->type == EXECUTABLE || args->type == ENV_VA)
			{
				free(str[i]);
				str[i] = ms_strdup(args->value, data);
				i++;
			}
		}
		args = args->next;
	}
	str[i] = NULL;
	return (str);
}
