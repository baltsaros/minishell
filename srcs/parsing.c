/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:46 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/27 03:16:32 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*init_empty(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->cmd_flags = NULL;
	cmd->argument = NULL;
	cmd->delim = NULL;
	cmd->in = 0;
	cmd->out = 1;
	cmd->pipe = 0;
	cmd->index = 0;
	return (cmd);
}

t_cmd	*init_cmd(t_node *parsing, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (parsing && parsing->value[0] != '|')
	{
		// Get cmd
		if (i == 0)
			cmd->cmd = parsing->value;
		else
		{
			//AAAAAAAAAARGH
			// Get flags
			if (parsing->value[0] == '-')
				cmd->cmd_flags = parsing->value;
			// Get argument
			else if (parsing->type == WORD)
				cmd->argument = parsing->value;
			// Get delim
			else if (!ft_strncmp(parsing->value, "<<", 2))
				cmd->delim = parsing->next->value;
			// Get in
			// It's in progress but not commited
			// Get out
			// It's in progress but not commited
			// Get pipe
			else if (parsing->next->value[0] == '|')
			{
				cmd->pipe = 1;
				i++;
			}
		}
		i++;
		parsing = parsing->next;
	}
	cmd->index = i;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*get_cmd(t_node	*parsing)
{
	t_cmd	*first_cmd;
	//t_cmd	*args;
	// /t_cmd	*new_con;

	first_cmd = init_empty();
	first_cmd = init_cmd(parsing, first_cmd);
	//args = first_cmd;
	//while (parsing)
	//{
	//	args = args->next;
	//	parsing = parsing->next;
	//}
	return  (first_cmd);
}

int	parsing(t_input *data, char *buf)
{
	(void)data;
	t_node	*parsing;
	t_cmd	*cmd;
	
	buf = remove_white_spaces(buf);
	parsing = get_args(buf, get_nb_elem(buf));
	free(buf);
	//while (parsing)
	//{
	//	printf("parsed value: %s\n", parsing->value);
	//	parsing = parsing->next;
	//}
	// More parsing
	cmd = get_cmd(parsing);
	while (cmd)
	{
		printf("cmd: %s\n", cmd->cmd);
		printf("flags: %s\n", cmd->cmd_flags);
		printf("argument: %s\n", cmd->argument);
		printf("delim: %s\n", cmd->delim);
		printf("in: %d\n", cmd->in);
		printf("out: %d\n", cmd->out);
		printf("\n");
		break ;
		cmd = cmd->next;
	}
	return (0);
}