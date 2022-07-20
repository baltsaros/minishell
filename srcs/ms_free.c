/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:35 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/20 09:54:23 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_free(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}

t_node	*ms_free_token(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = ms_token_del(node);
	node = ms_token_del(node);
	node = NULL;
	return (node);
}

t_env	*ms_free_envp(t_env *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = ms_envp_del(node);
	node = ms_envp_del(node);
	node = NULL;
	return (node);
}

void	ms_free_cmd(t_cmd *to_free)
{
	t_cmd	*tmp;

	if (!to_free)
		return ;
	while (to_free)
	{
		tmp = to_free->next;
		if (to_free->cmd)
			ms_free(to_free->cmd);
		if (to_free->delim)
			free(to_free->delim);
		if (to_free->in != 0)
			close(to_free->in);
		if (to_free->in_arg)
			free(to_free->in_arg);
		if (to_free->out != 1)
			close(to_free->out);
		if (to_free->out_arg)
			free(to_free->out_arg);
		free(to_free);
		to_free = tmp;
	}
}

void	ms_free_all(t_input *data)
{
	if (data->envp_n)
		ms_free_envp(data->envp_n);
	if (data->args)
		ms_free_token(data->args);
	if (data->cmds)
		ms_free_cmd(data->cmds);
	if (data->envp)
		ms_free(data->envp);
	free(data->prompt);
}
