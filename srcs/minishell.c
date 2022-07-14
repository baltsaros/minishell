#include "../include/minishell.h"

void	prompt(t_input *data)
{
	g_status = 0;
	while (1)
	{
		if (signal(SIGINT, signal_handling) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			printf("[ERROR]: SIGNAL HANDLER FAILED!\n");
		data->buf = readline("YAMSP-1.6$ ");
		if (!data->buf)
		{
			yo_exit(data);
		}
		else if (is_right_buf(data->buf) != 1)
		{
			add_history(data->buf);
			check_field(&data->buf, data);
			data_init(data);
			// ms_envp_print(data->envp_n);
			// ms_token_print(data->args);
			if (parsing(data) == 0)
			{
				// asterisks(data);
				execute(data);
				ms_free_token(data->args);
				// ms_free_cmd(data->cmds);
			}
			//else
			//	ms_free_token(data->args);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input	data;

	(void)argv;
	if (argc != 1)
	{
		too_many_argv();
		exit(EXIT_FAILURE);
	}
	envp_init(&data, envp);
	prompt(&data);
	return ((g_status >> 8) & 0xff);
}
