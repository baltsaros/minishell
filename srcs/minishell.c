#include "../include/minishell.h"

void	prompt(t_input *data)
{
	while (1)
	{
		if (signal(SIGINT, signal_handling) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			printf("[ERROR]: SIGNAL HANDLER FAILED!\n");
		data->buf = readline(data->prompt);
		if (!data->buf)
			yo_exit(data);
		else if (is_right_buf(data->buf) != 1)
		{
			add_history(data->buf);
			check_field(data, data->buf);
			data_init(data);
			// ms_envp_print(data->envp_n);
			// ms_token_print(data->args);
			
			token_simplification(data);
			if (!parsing(data))
			{
				asterisks(data, data->cmds);
				execute(data);
				//ms_free_token(data->args);
				// ms_free_cmd(data->cmds);
			}
			// else
				//ms_free_token(data->args);
		}
		free(data->buf);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input	data;

	(void)argv;
	if (argc != 1)
	{
		invalid_argv();
		exit(EXIT_FAILURE);
	}
	welcome();
	g_status = 0;
	envp_init(&data, envp);
	data.prompt = ms_strdup("YAMSP-1.6$ ", &data);
	prompt(&data);
	return ((g_status >> 8) & 0xff);
}
