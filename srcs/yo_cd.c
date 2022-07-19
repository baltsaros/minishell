#include "../include/minishell.h"

int	yo_cd(t_input *data)
{
	if (!data->cmds->cmd[1])
		return (0);
	else if (chdir(data->cmds->cmd[1]))
	{
		write(2, "YAMSP: ", 7);
		perror("cd");
		g_status = errno;
		return (g_status);
	}
	return (0);
}
