/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:08 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 11:42:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg(char *s)
{
	write(2, "YAMSP: ", 7);
	write(2, "unset: `", 8);
	write(2, s, ft_strlen(s));
	write(2, "': not a valid identifier\n", 26);
	g_status = 1;
}

// remove envp from linked lists
static int	check_envp(char *s, t_env *envp_n, int n, t_input *data)
{
	if (!envp_n)
		return (0);
	if (ft_strchr(s, '='))
	{
		error_msg(s);
		return (0);
	}
	if (!ft_strncmp(s, data->envp_n->type, n))
	{
		data->envp_n = ms_envp_del(data->envp_n);
		return (1);
	}
	while (envp_n)
	{
		if (!ft_strncmp(s, envp_n->type, n))
		{
			envp_n = ms_envp_del(envp_n);
			return (1);
		}
		envp_n = envp_n->next;
	}
	return (0);
}

// remove envp from char**
static void	remove_envp(t_input *data, char *type)
{
	int		size;
	char	**tmp;

	size = 0;
	data->i = 0;
	data->j = 0;
	while (data->envp[size])
		size++;
	tmp = ms_malloc(sizeof(*tmp) * (size), data);
	while (data->envp[data->i] && ft_strncmp(data->envp[data->i],
			type, ft_strlen(type)))
	{
		tmp[data->i] = ms_strdup(data->envp[data->i], data);
		data->i++;
	}
	data->j++;
	while (data->envp[data->i + data->j])
	{
		tmp[data->i] = ms_strdup(data->envp[data->i + data->j], data);
		data->i++;
	}
	tmp[data->i] = NULL;
	ms_free(data->envp);
	data->envp = tmp;
}

int	yo_unset(t_input *data)
{
	int	i;
	int	len;

	i = 1;
	g_status = 0;
	while (data->cmds->cmd[i])
	{
		len = ft_strlen(data->cmds->cmd[i]) + 1;
		if (check_envp(data->cmds->cmd[i], data->envp_n, len, data))
			remove_envp(data, data->cmds->cmd[i]);
		++i;
	}
	return (0);
}
