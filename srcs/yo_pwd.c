#include "../include/minishell.h"

int	yo_pwd(t_input *data)
{
	char	*ret;

	ret = NULL;
	ret = getcwd(NULL, 0);
	if (!ret)
	{
		perror("pwd");
		g_status = errno;
	}
	else
	{
		write(data->cmds->out, ret, ft_strlen(ret));
		write(data->cmds->out, "\n", 1);
		g_status = 0;
	}
	return (0);
}
