#include "../include/minishell.h"

int	yo_env(t_input *data)
{
	t_env	*tmp;

	tmp = data->envp_n;
	if (data->cmds->cmd[1])
	{
		data->status = 127;
		write(2, "env: ", 5);
		write(2, data->cmds->cmd[1], ft_strlen(data->cmds->cmd[1]));
		write(2, ": No such file or directory\n", 28);
		return (data->status);
	}
	data->i = 0;
	while (tmp && data->i < data->envp_len)
	{
		write(data->cmds->out, tmp->type, ft_strlen(tmp->type));
		if (tmp->value)
		{
			write(data->cmds->out, "=", 1);
			write(data->cmds->out, tmp->value, ft_strlen(tmp->value));
		}
		write(data->cmds->out, "\n", 1);
		tmp = tmp->next;
		data->i++;
	}
	return (0);
}
