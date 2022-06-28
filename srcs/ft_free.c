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
