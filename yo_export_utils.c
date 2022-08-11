/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:57 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 14:02:40 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_dstrlen(char **dstr)
{
	size_t	i;

	i = 0;
	while (dstr[i])
		++i;
	return (i);
}

// add to envp char**
void	add_envp(t_input *data, char *type, char *value)
{
	int		size;
	char	**tmp;
	char	*str;

	size = ms_dstrlen(data->envp);
	data->i = 0;
	tmp = ms_malloc((sizeof(tmp) * (size + 2)), data);
	while (data->envp[data->i])
	{
		tmp[data->i] = ms_strdup(data->envp[data->i], data);
		data->i++;
	}
	str = ft_strjoin(type, "=");
	alloc_check_small(str, data);
	if (value)
		tmp[data->i] = ft_strjoin(str, value);
	else
		tmp[data->i] = ms_strdup(str, data);
	tmp[data->i + 1] = NULL;
	free(str);
	ms_free(data->envp);
	data->envp = tmp;
	type = NULL;
	value = NULL;
}
