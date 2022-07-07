#include "../include/minishell.h"

void	alloc_check(char **str)
{
	if (!str)
	{
		write(2, "Allocation failed\n", 18);
		exit(1);
	}
	// if ((!str[0]))
	// {
	// 	write(2, "Invalid arg\n", 12);
	// 	ft_free(str);
	// 	exit(1);
	// }
}

void	alloc_check_small(void *str)
{
	if (!str)
	{
		write(2, "Allocation failed\n", 18);
		exit(1);
	}
}

void	alloc_check_token(t_node *new, t_node **node)
{
	if (!new)
	{
		write(2, "Allocation failed\n", 18);
		*node = ft_free_token(*node);
		exit(1);
	}
}

void	alloc_check_envp(t_env *new, t_env **node)
{
	if (!new)
	{
		write(2, "Allocation failed\n", 18);
		*node = ft_free_envp(*node);
		exit(1);
	}
}
