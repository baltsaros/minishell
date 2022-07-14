#include "../include/minishell.h"

int	is_the_next_is_word(t_node *args)
{
	t_node	*elem;

	elem = args;
	if (elem->next->type != WORD)
		return (1);
	return (0);
}

t_cmd	*print_syntax_error_cmd(t_node *args)
{
	if (!args->next)
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, "newline", 7);
		write(2, "'\n", 2);
	}
	else if (args->next->type != WORD)
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, args->next->value, ft_strlen(args->value));
		write(2, "'\n", 2);
	}
	return (NULL);
}

int	print_syntax_error_bool(t_node *args)
{
	if (!args->next)
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, "newline", 7);
		write(2, "'\n", 2);
	}
	else if (args->next->type != WORD)
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, args->next->value, ft_strlen(args->value));
		write(2, "'\n", 2);
	}
	return (1);
}
