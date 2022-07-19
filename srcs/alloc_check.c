#include "../include/minishell.h"

void	alloc_check_big(char **str, t_input *data)
{
	if (!str)
	{
		write(2, "YAMSP: ", 7);
		write(2, "allocation failed\n", 18);
		ms_free_all(data);
		exit(1);
	}
}

void	alloc_check_small(void *str, t_input *data)
{
	if (!str)
	{
		write(2, "YAMSP: ", 7);
		write(2, "allocation failed\n", 18);
		ms_free_all(data);
		exit(1);
	}
}

void	alloc_check_token(t_node *new, t_node **node)
{
	if (!new)
	{
		write(2, "YAMSP: ", 7);
		write(2, "allocation failed\n", 18);
		*node = ms_free_token(*node);
		exit(1);
	}
}

void	alloc_check_envp(t_env *new, t_env **node)
{
	if (!new)
	{
		write(2, "YAMSP: ", 7);
		write(2, "allocation failed\n", 18);
		*node = ms_free_envp(*node);
		exit(1);
	}
}
