#include "../include/minishell.h"

static int	ft_isdigit_sign(int c)
{
	if ((c >= 48 && c <= 57) || c == '+' || c == '-')
		return (1);
	else
		return (0);
}

static int	check_nonnumeric(t_input *data)
{
	if (!data->cmds->cmd[1])
	{
		write(data->cmds->out, "exit\n", 5);
		g_status = 0;
		return (0);
	}
	data->i = 0;
	while (data->cmds->cmd[1][data->i])
	{
		if (!ft_isdigit_sign(data->cmds->cmd[1][data->i]))
		{
			write(data->cmds->out, "exit\n", 5);
			write(2, "YAMSP-1.6: exit: ", 17);
			write(2, data->cmds->cmd[1], ft_strlen(data->cmds->cmd[1]));
			write(2, ": numeric argument required\n", 28);
			g_status = 2;
			return (0);
		}
		data->i++;
	}
	return (1);
}

static int	check_amount(t_input *data)
{
	if (data->cmds->len_cmd > 2)
	{
		write(data->cmds->out, "exit\n", 5);
		write(2, "YAMSP-1.6: exit: ", 17);
		write(2, "too many arguments\n", 19);
		g_status = 1;
		return (0);
	}
	return (1);
}

int	yo_exit(t_input *data)
{
	if (!data->buf)
	{
		g_status = 1;
		exit(g_status);
	}
	ms_free_envp(data->envp_n);
	ms_free_token(data->args);
	ms_free(data->envp);
	// if (data->wild)
	// 	ms_free_token(data->wild);
	// ms_free_cmd(data->cmds);
	if (!check_nonnumeric(data))
		exit(g_status);
	if (!check_amount(data))
		exit(g_status);
	g_status = ft_atoi(data->cmds->cmd[1]);
	write(data->cmds->out, "exit\n", 5);
	exit (g_status);
}
