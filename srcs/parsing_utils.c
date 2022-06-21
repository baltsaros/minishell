/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:38:20 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/06/21 15:17:05 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(t_node *args)
{
	t_node *tmp;

	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp);
	}
}

void	free_data_line(char **line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

bool	is_a_right_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (true);
	else if (!ft_strncmp(cmd, "-n", 2))
		return (true);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (true);
	else if (!ft_strncmp(cmd, "export", 6))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (true);
	else if (!ft_strncmp(cmd, "env", 3))
		return (true);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (true);
	return (false);
}

t_node	*init_first_elem_arg(char *line)
{
	t_node	*first_elem;

	first_elem = (t_node *) malloc (sizeof(t_node));
	if (!first_elem)
		return (NULL);
	first_elem->type = WORD;
	first_elem->type = init_type_builtin(first_elem);
	first_elem->value = line;
	first_elem->next = NULL;
	first_elem->prev = NULL;
	return (first_elem);
}

t_node	*parse_args(char **line)
{
	t_node 	*first_elem;
	t_node	*args;
	t_node	*new_con;
	int		i;

	first_elem = init_first_elem_arg(line[0]);
	if (!first_elem)
		return (NULL);
	args = first_elem;
	i = 1;
	while (line[i])
	{
		new_con = (t_node *) malloc (sizeof(t_node));
		if (!new_con)
			return (NULL);
		new_con->type = WORD;
		new_con->type = init_type_builtin(new_con);
		new_con->value = line[i];
		new_con->next = NULL;
		new_con->prev = args;
		args->next = new_con;
		args = args->next;
		i++;
	}
	return (first_elem);
}

int	init_type_builtin(t_node *cmd)
{
	if (cmd->type == WORD)
	{
		if (!ft_strncmp(cmd->value, "echo", 4))
			return (BI_ECHO);
		else if (!ft_strncmp(cmd->value, "-n", 2))
			return (BI_ECHON);
		else if (!ft_strncmp(cmd->value, "cd", 2))
			return (BI_CD);
		else if (!ft_strncmp(cmd->value, "pwd", 3))
			return (BI_PWD);
		else if (!ft_strncmp(cmd->value, "export", 6))
			return (BI_EXPORT);
		else if (!ft_strncmp(cmd->value, "unset", 5))
			return (BI_UNSET);
		else if (!ft_strncmp(cmd->value, "env", 3))
			return (BI_ENV);
		else if (!ft_strncmp(cmd->value, "exit", 4))
			return (BI_EXIT);
		else
			return (WORD);
	}
	return (0);
}

