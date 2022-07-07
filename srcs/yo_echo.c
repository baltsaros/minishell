#include "../include/minishell.h"

static void	echo_with_flag(t_cmd *com)
{
	int	i;

	i = 2;
	while (com->cmd[i])
	{
		write(com->out, com->cmd[i], ft_strlen(com->cmd[i]));
		++i;
	}
}

static void	echo_without_flag(t_cmd *com)
{
	int	i;

	i = 1;
	while (com->cmd[i])
	{
		write(com->out, com->cmd[i], ft_strlen(com->cmd[i]));
		++i;
	}
	write(com->out, "/n", 1);
}

int	yo_echo(t_input *data)
{

	if (!data->cmds->cmd[1])
		write(data->cmds->out, "\n", 1);
	else if (strncmp(data->cmds->cmd[1], "-n", 2) == 0)
		echo_with_flag(data->cmds);
	else
		echo_without_flag(data->cmds);
	return (0);
}
