#include "../include/minishell.h"

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
	return (1);
}

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

static void	export_var(t_input *data, int *i)
{
	data->type = ms_strdup(data->cmds->cmd[*i], data);
	if (!data->cmds->cmd[*i + 1])
		data->value = NULL;
	else if (data->cmds->cmd[*i + 1] && data->cmds->cmd[*i + 1][0] == '=')
	{
		if (data->cmds->cmd[*i + 2])
		{
			data->value = ms_strdup(data->cmds->cmd[*i + 2], data);
			++(*i);
		}
		else
			data->value = ms_strdup("", data);
		++(*i);
	}
	else
		data->value = NULL;
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
		export_var(data, &i);
		if (!check_duplicate(data, data->type, data->value))
		{
			data->envp_tmp = ms_envp_new(data->type, data->value, data);
			ms_envp_back(&data->envp_n, data->envp_tmp);
			add_envp(data, data->type, data->value);
		}
		++i;
	}
	return (0);
}
