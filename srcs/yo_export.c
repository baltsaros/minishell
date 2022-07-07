#include "../include/minishell.h"

static void	add_envp(t_input *data, char *type, char *value)
{
	int		size;
	char	**tmp;

	size = 0;
	data->i = 0;
	while (data->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(*tmp) * (size + 2));
	alloc_check(tmp);
	while (data->envp[data->i])
	{
		tmp[data->i] = data->envp[data->i];
		data->i++;
	}
	if (value)
	{
		data->tmp = ft_strjoin(type, "=");
		tmp[data->i] = ft_strjoin(data->tmp, value);
	}
	else
		tmp[data->i] = type;
	// alloc_check_small(tmp[data->i]);
	tmp[data->i + 1] = NULL;
	data->envp = tmp;
	type = NULL;
	value = NULL;
}

static int	check_duplicate(t_input *data, char *type, char *value)
{
	data->envp_tmp = data->envp_n;
	while (data->envp_tmp && ft_strncmp(data->envp_tmp->type, type, ft_strlen(type) + 1))
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

int		yo_export(t_input *data)
{
	int	i;

	if (data->argc == 1)
	{
		print_envp(data->envp_n);
		return (0);
	}
	i = 1;
	while (data->argv[i] && data->argv[i][0] != '=')
		++i;
	data->type = ft_strdup(data->argv[i - 1]);
	if (data->argv[i + 1])
		data->value = ft_strdup(data->argv[i + 1]);
	else
		data->value = NULL;
	if (check_duplicate(data, data->type, data->value))
		return (0);
	data->envp_tmp = ft_envp_new(data->type, data->value);
	ft_envp_back(&data->envp_n, data->envp_tmp);
	add_envp(data, data->type, data->value);
	return (0);
}
