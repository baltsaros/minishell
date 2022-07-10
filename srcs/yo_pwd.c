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
