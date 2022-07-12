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
	{
		write(data->cmds->out, ret, ft_strlen(ret));
		write(data->cmds->out, "\n", 1);
	}
	return (0);
}
