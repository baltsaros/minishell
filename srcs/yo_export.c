#include "../include/minishell.h"

static int	check_duplicate(t_input *data, char *type, char *value)
{
	data->envp_tmp = data->envp_n;
	while (data->envp_tmp && ft_strncmp(data->envp_tmp->type,
			type, ft_strlen(type) + 1))
		data->envp_tmp = data->envp_tmp->next;
	if (!data->envp_tmp)
		return (0);
	if (data->envp_tmp->value)
		free(data->envp_tmp->value);
	data->envp_tmp->value = value;
	add_envp(data, type, value);
	return (1);
}

static void	print_envp(t_env *envp)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = envp;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->type, tmp->value);
		else
			printf("declare -x %s\n", tmp->type);
		tmp = tmp->next;
	}
}

static void	export_var(t_input *data, int *i)
{
	data->type = ft_strdup(data->cmds->cmd[*i]);
	if (!data->cmds->cmd[*i + 1])
		data->value = NULL;
	else if (data->cmds->cmd[*i + 1] && data->cmds->cmd[*i + 1][0] == '=')
	{
		if (data->cmds->cmd[*i + 2])
		{
			data->value = ft_strdup(data->cmds->cmd[*i + 2]);
			++(*i);
		}
		else
			data->value = ft_strdup("");
		++(*i);
	}
	else
		data->value = NULL;
}

int	yo_export(t_input *data)
{
	int	i;

	if (data->cmds->len_cmd == 1)
	{
		print_envp(data->envp_n);
		return (0);
	}
	i = 1;
	while (data->cmds->cmd[i])
	{
		export_var(data, &i);
		if (!check_duplicate(data, data->type, data->value))
		{
			data->envp_tmp = ft_envp_new(data->type, data->value);
			ft_envp_back(&data->envp_n, data->envp_tmp);
			add_envp(data, data->type, data->value);
		}
		++i;
	}
	return (0);
}
