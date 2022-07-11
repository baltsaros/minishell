#include "../include/minishell.h"

void	add_envp(t_input *data, char *type, char *value)
{
	int		size;
	char	**tmp;

	size = ft_envp_size(data->envp_n);
	data->i = 0;
	tmp = (char **)malloc(sizeof(*tmp) * (size + 2));
	alloc_check(tmp);
	while (data->envp[data->i])
	{
		tmp[data->i] = ft_strdup(data->envp[data->i]);
		data->i++;
	}
	if (value)
	{
		data->tmp = ft_strjoin(type, "=");
		tmp[data->i] = ft_strjoin_free(data->tmp, value);
	}
	else
		tmp[data->i] = ft_strdup(type);
	tmp[data->i + 1] = NULL;
	ft_free(data->envp);
	data->envp = tmp;
	type = NULL;
	value = NULL;
}
