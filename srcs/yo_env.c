#include "../include/minishell.h"

int		yo_env(t_input *data)
{
	t_env	*tmp;

	tmp = data->envp_n;
	if (data->cmds->cmd[1] && data->cmds->cmd[1][0] != '|')		// neeed to find a better way to display error
	{
		data->status = 127;
		write(2, "env: ", 5);
		write(2, data->cmds->cmd[1], ft_strlen(data->cmds->cmd[1]));
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
