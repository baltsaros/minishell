#include "../include/minishell.h"

int	yo_cd(t_input *data)
{
	if (!data->cmds->cmd[1])
		return (0);
	else if (chdir(data->cmds->cmd[1]))
	{
		perror("cd");
		data->status = errno;
		return (data->status);
	}
	return (0);
}
