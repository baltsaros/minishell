#include "../include/minishell.h"

void	add_envp(t_input *data, char *type, char *value)
{
	int		size;
	char	**tmp;

	size = ms_envp_size(data->envp_n);
	data->i = 0;
	tmp = ms_malloc((sizeof(*tmp) * (size + 2)), data);
	while (data->envp[data->i])
	{
		tmp[data->i] = ft_strdup(data->envp[data->i]);
		data->i++;
	}
	if (value)
	{
		data->tmp = ft_strjoin(type, "=");
		tmp[data->i] = ms_strjoin_free(data->tmp, value);
	}
	else
		tmp[data->i] = ft_strdup(type);
	tmp[data->i + 1] = NULL;
	ms_free(data->envp);
	data->envp = tmp;
	type = NULL;
	value = NULL;
}
