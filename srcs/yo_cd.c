#include "../include/minishell.h"

int	yo_cd(t_input *data)
{
	if (!data->cmds->cmd[1])
		return (0);
	else if (chdir(data->cmds->cmd[1]))
	{
		data->status = 1;
		perror("cd");
		return (data->status);
	}
	return (0);
}
