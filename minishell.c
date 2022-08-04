/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:38:28 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 12:13:05 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_input *data)
{
	while (1)
	{
		if (signal(SIGINT, signal_main) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			error_check(-1, "in signals ", 11, data);
		data->buf = readline(data->prompt);
		if (!data->buf)
			yo_exit(data);
		else if (is_right_buf(data->buf) != 1)
		{
			add_history(data->buf);
			if (!check_field(data, data->buf))
			{
				data_init(data);
				token_simplification(data);
				// ms_token_print(data->args);
				if (!parsing(data))
					execute(data);
				ms_free_token(data->args);
				ms_free_cmd(data->cmds);
			}
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
