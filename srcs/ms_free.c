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

void	ms_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->delim)
			free(cmd->delim);
		if (cmd->in_arg)
			free(cmd->in_arg);
		if (cmd->out_arg)
			free(cmd->out_arg);
		free(cmd);
		cmd = tmp;
	}
}

void	ms_free_node_elems(t_env *tmp)
{
	free(tmp->type);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
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
}
