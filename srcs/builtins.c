#include "../include/minishell.h"

int	yo_pwd(t_input *data)
{
	char	*ret;

	ret = NULL;
	ret = getcwd(NULL, 0);
	if (!ret)
	{
		data->status = 1;
		perror("pwd");
	}
	else
		ft_printf("%s\n", ret);
	return (0);
}

int	yo_cd(t_input *data)
{
	if (!data->argv[1])
		return (0);
	else if (chdir(data->argv[1]))
	{
		data->status = 1;
		perror("cd");
	}
	return (0);
}

int		yo_env(t_input *data)
{
	t_env	*tmp;

	tmp = data->envp_n;
	if (data->argv[1] && data->argv[1][0] != '|')		// neeed to find a better way to display error
	{
		data->status = 127;
		write(2, "env: ", 5);
		write(2, data->argv[1], ft_strlen(data->argv[1]));
		write(2, ": No such file or directory\n", 28);
		return (data->status);
	}
	printf("env\n");
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->type, tmp->value);
		else
			printf("%s\n", tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

int		yo_unset(t_input *data)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = data->envp_n;
	while (data->argv[i])
	{
		if (check_envp(data->argv[i], data->envp_n, ft_strlen(data->argv[i])))
		{
			while (ft_strncmp(data->argv[i], tmp->type, ft_strlen(data->argv[i]) + 1))
			{
				tmp = tmp->next;
			}
			tmp = ft_envp_del(tmp);
		++i;
		}
	}
	return (0);
}

int		yo_exit(t_input *data)
{
	ft_free_envp(data->envp_n);
	ft_free_token(data->args);
	if (data->wild)
		ft_free_token(data->wild);
	printf("exit\n");
	if (data->argv[1])
	{
		data->status = ft_atoi(data->argv[1]);
		exit (data->status);
	}
	exit (data->status);
}
