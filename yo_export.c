/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:00 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 13:11:20 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_duplicate(t_input *data, char *type, char *value)
{
	data->envp_tmp = data->envp_n;
	while (data->envp_tmp && ft_strcmp(data->envp_tmp->type, type))
		data->envp_tmp = data->envp_tmp->next;
	if (!data->envp_tmp)
		return (0);
	if (data->envp_tmp->value)
		free(data->envp_tmp->value);
	data->envp_tmp->value = value;
	add_envp(data, type, value);
	free(type);
	return (1);
}

// print all envp, including ones without values
static void	print_envp(t_input *data, t_env *envp)
{
	t_env	*tmp;
	int		len;

	tmp = NULL;
	tmp = envp;
	while (tmp)
	{
		len = ft_strlen(tmp->type);
		write(data->cmds->out, "declare -x ", 11);
		write(data->cmds->out, tmp->type, len);
		if (tmp->value)
		{
			write(data->cmds->out, "=", 1);
			len = ft_strlen(tmp->value);
			write(data->cmds->out, tmp->value, len);
		}
		write(data->cmds->out, "\n", 1);
		tmp = tmp->next;
	}
}

static void	error_msg(int c)
{
	write(2, "YAMSP: ", 7);
	write(2, "export: `", 9);
	write(2, &c, 1);
	write(2, "': not a valid identifier\n", 26);
	g_status = 1;
}

// update linked list envp
static void	export_var(t_input *data, char *s)
{
	while (s[data->i] && ft_isalnum(s[data->i]))
		data->i++;
	if (data->i == 0 && s[data->i])
	{
		error_msg(s[data->i]);
		return ;
	}
	data->type = ms_strndup(s, data->i, data);
	if (s[data->i] && s[data->i + 1])
	{
		data->i++;
		if (s[data->i])
			data->value = ms_strdup(s + data->i, data);
	}
	else if (s[data->i])
			data->value = ms_strdup("", data);
	if (!check_duplicate(data, data->type, data->value))
	{
		data->envp_tmp = ms_envp_new(data->type, data->value, data);
		ms_envp_back(&data->envp_n, data->envp_tmp);
		add_envp(data, data->type, data->value);
	}
}

int	yo_export(t_input *data)
{
	int	i;

	g_status = 0;
	if (data->cmds->len_cmd == 1)
	{
		print_envp(data, data->envp_n);
		return (0);
	}
	i = 1;
	while (data->cmds->cmd[i])
	{
		data->i = 0;
		data->type = NULL;
		data->value = NULL;
		if (!data->cmds->cmd[i][0])
		{
			++i;
			continue ;
		}
		export_var(data, data->cmds->cmd[i]);
		++i;
	}
	return (0);
}
