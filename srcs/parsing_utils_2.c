/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:41:09 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/20 17:12:26 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_size_cmd(t_node	*args)
{
	int	i;

	i = 0;
	while (args && args->type != PIPE)
	{
		if (args->type != WSPACE
			&& args->type != QUOTE && args->type != QUOTE_D)
		{
			if (!is_between_d_quote(args) || !is_between_quote(args))
			{
				if (args->prev && (args->prev->type == QUOTE
						|| args->prev->type == QUOTE_D))
					i++;
			}
			else
				i++;
		}
		if (args->type == ENV_VA && args->prev && args->prev->type == ENV_VA)
			i--;
		if (args->type == IN_ARG || args->type == OUT_ARG
			|| args->type == DOLLAR || !args->value || args->type == 0)
			i--;
		args = args->next;
	}
	// printf("I: %d\n", i);
	return (i);
}

char	**init_cmd(t_node *args, t_input *data)
{
	int		size;
	int		i;
	char	**str;

	size = get_size_cmd(args);
	if (size == 0)
		return (NULL);
	i = 0;
	str = ms_malloc((size + 1) * sizeof(char *), data);
	while (args && args->type != PIPE)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			if (args->type == WORD || args->type == ASTER
				|| args->type == EXECUTABLE || args->type == ENV_VA
				|| args->type == ENV_VA_BR || args->type == ENV_P
				|| args->type == DOLLAR_VAR || args->type == SLASH)
			{
				str[i] = ms_strdup(args->value, data);
				i++;
			}
			else if (args->type == EMPTY_ARG)
			{
				str[i] = ms_strdup("\0", data);
				i++;
			}
		}
		args = args->next;
	}
	str[i] = NULL;
	return (str);
}
