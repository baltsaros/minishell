#include "../include/minishell.h"

void	ft_free(char *str[])
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

t_node	*ft_free_token(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = ft_token_del(node);
	node = ft_token_del(node);
	node = NULL;
	return (node);
}

t_env	*ft_free_envp(t_env *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = ft_envp_del(node);
	node = ft_envp_del(node);
	node = NULL;
	return (node);
}

void	ft_free_cmd(t_cmd *cmd)
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

void	ft_free_node_elems(t_env *tmp)
{
	free(tmp->type);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}
