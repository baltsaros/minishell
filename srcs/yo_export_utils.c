/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:57 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/25 12:37:08 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ms_dstrlen(char **dstr)
{
	size_t	i;

	i = 0;
	while (dstr[i])
		++i;
	return (i);
}

void	add_envp(t_input *data, char *type, char *value)
{
	int		size;
	char	**tmp;

	size = ms_dstrlen(data->envp);
	data->i = 0;
	tmp = ms_malloc((sizeof(tmp) * (size + 2)), data);
	while (data->envp[data->i])
	{
		tmp[data->i] = ms_strdup(data->envp[data->i], data);
		data->i++;
	}
	if (value)
	{
		data->tmp = ft_strjoin(type, "=");
		alloc_check_small(data->tmp, data);
		tmp[data->i] = ms_strjoin_free(data->tmp, value, data);
	}
	else
		tmp[data->i] = ms_strdup(type, data);
	tmp[data->i + 1] = NULL;
	ms_free(data->envp);
	data->envp = tmp;
	type = NULL;
	value = NULL;
}
