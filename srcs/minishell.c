#include "../include/minishell.h"

int	is_right_buf(char	*buf)
{
	int	i;

	i = 0;
	if (buf[0] == '\0')
		return (1);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
			&& buf[i] != '\v' && buf[i] != '\f' && buf[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

void	prompt(t_input *data)
{
	while (1)
	{
		data->buf = readline("minishell$ ");
		if (!data->buf)
			yo_exit(data);
		else if (is_right_buf(data->buf) != 1)
		{
			add_history(data->buf);
			check_field(&data->buf, data);
			data_init(data);
			if (parsing(data) == 0)
			{
				execute(data);
				ft_free_token(data->args);
				ft_free_cmd(data->cmds);
			}
			else
				ft_free_token(data->args);
		}
		//asterisks(&data);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input 			data;
	struct sigaction	act;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	if (sigaction(SIGINT, &act, NULL) == -1
		|| sigaction(SIGQUIT, &act, NULL) == -1)
		printf("[ERROR]: Signal handler failed\n");
	envp_init(&data, envp);
	prompt(&data);
	return ((data.status >> 8) & 0xff);
}
