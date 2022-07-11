#include "../include/minishell.h"

static void	remove_envp(t_input *data, char *type)
{
	int		size;
	char	**tmp;

	size = 0;
	data->i = 0;
	while (data->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(*tmp) * size);
	alloc_check(tmp);
	while (data->envp[data->i] && ft_strncmp(data->envp[data->i], type, ft_strlen(type)))
	{
		tmp[data->i] = data->envp[data->i];
		data->i++;
	}
	free(data->envp[data->i]);
	data->i++;
	while (data->envp[data->i])
	{
		tmp[data->i] = data->envp[data->i];
		data->i++;
	}
	tmp[data->i] = NULL;
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
	return (0);
}
