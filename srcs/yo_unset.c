#include "../include/minishell.h"

static int	check_envp(char *c, t_env *envp_n, int n)
{
	if (!envp_n)
		return (0);
	while (envp_n)
	{
		if (!ft_strncmp(c, envp_n->type, n))
		{
			envp_n = ms_envp_del(envp_n);
			return (1);
		}
		envp_n = envp_n->next;
	}
	return (0);
}

static void	remove_envp(t_input *data, char *type)
{
	int		size;
	char	**tmp;

	size = 0;
	data->i = 0;
	data->j = 0;
	while (data->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(*tmp) * size);
	alloc_check(tmp);
	while (data->envp[data->i] && ft_strncmp(data->envp[data->i],
			type, ft_strlen(type)))
	{
		tmp[data->i] = ft_strdup(data->envp[data->i]);
		data->i++;
	}
	data->j++;
	while (data->envp[data->i + data->j])
	{
		tmp[data->i] = ft_strdup(data->envp[data->i + data->j]);
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
	while (data->cmds->cmd[i])
	{
		len = ft_strlen(data->cmds->cmd[i]) + 1;
		if (check_envp(data->cmds->cmd[i], data->envp_n, len))
			remove_envp(data, data->cmds->cmd[i]);
		++i;
	}
	data->status = 0;
	return (0);
}
