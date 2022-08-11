/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:38:28 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 14:24:48 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// read from input, check whether it is correct or not; if correct,
// create tokens, simplify them, build commands and execute;
// then free what is not needed anymore and repeat;
// check for ctrl+c all the time
void	prompt(t_input *data)
{
	while (1)
	{
		if (signal(SIGINT, signal_main) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			error_check(-1, "", data);
		data->buf = readline(data->prompt);
		if (!data->buf)
			yo_exit(data);
		else if (is_right_buf(data->buf) != 1)
		{
			if (!check_closed(data, data->buf))
				add_history(data->buf);
			if (!check_field(data, data->buf))
			{
				data_init(data);
				token_simplification(data);
				if (!parsing(data))
					execute(data);
				ms_free_token(data->args);
				ms_free_cmd(data->cmds);
			}
		}
		free(data->buf);
	}
}

// create welcome message; initialize envp variable
// create prompt's name and then call it
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
