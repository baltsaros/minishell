#include "../include/minishell.h"

static void	create_envp(t_input *data, char *envp[])
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (envp[i])
	{
		start = 0;
		end = 0;
		while (envp[i][start] != '=')
			++start;
		while (envp[i][end])
			++end;
		data->type = ft_strndup(envp[i], start);
		data->value = ft_strndup(envp[i] + start + 1, end - start - 1);
		data->envp_tmp = ft_envp_new(data->type, data->value);
		ft_envp_back(&data->envp_n, data->envp_tmp);
		++i;
	}
	data->envp_len = i;
}

static void	copy_envp(t_input *data, char *envp[])
{
	int	size;

	size = 0;
	while(envp[size])
		++size;
	data->envp = (char **)malloc(sizeof(*data->envp) * (size + 1));
	alloc_check(data->envp);
	data->i = 0;
	while (envp[data->i])
	{
		data->envp[data->i] = envp[data->i];
		data->i++;
	}
	data->envp[data->i] = NULL;
}

void	envp_init(t_input *data, char *envp[])
{
	static struct builtin builtins[] =
	{
		{"pwd", &yo_pwd},
		{"cd", &yo_cd},
		{"echo", &yo_echo},
		{"export", &yo_export},
		{"env", &yo_env},
		{"unset", &yo_unset},
		{"exit", &yo_exit}
	};
	copy_envp(data, envp);
	data->envp_n = NULL;
	data->type = NULL;
	data->value = NULL;
	data->tmp = NULL;
	data->i = 0;
	data->j = 0;
	data->envp_tmp = NULL;
	data->node_tmp = NULL;
	data->builtins = builtins;
	create_envp(data, data->envp);
	//ft_envp_print(data->envp_n);
}

void	data_init(t_input *data)
{
	if (!data->buf || !*data->buf)
		return ;
	data->status = 0;
	data->in = 0;
	data->out = 1;
	data->args = NULL;
	create_token(data);
	data->argc = ft_token_size(data->args);
	// ft_token_print(data->args);
}
