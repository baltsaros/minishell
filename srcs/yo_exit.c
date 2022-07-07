#include "../include/minishell.h"

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
