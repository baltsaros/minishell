/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:30:32 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 14:30:35 by abuzdin          ###   ########.fr       */
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
	char	**tmp;
	char	*str;

	data->k = ms_dstrlen(data->envp);
	data->i = 0;
	tmp = ms_malloc((sizeof(tmp) * (data->k + 2)), data);
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
	alloc_check_small(tmp[data->i], data);
	tmp[data->i + 1] = NULL;
	free(str);
	ms_free(data->envp);
	data->envp = tmp;
	type = NULL;
	value = NULL;
}
