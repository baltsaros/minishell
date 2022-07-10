#include "../include/minishell.h"

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
