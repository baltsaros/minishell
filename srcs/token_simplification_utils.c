#include "../include/minishell.h"

int	is_between_d_quote(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == QUOTE_D)
		return (1);
	while (args->prev && args->type != QUOTE_D && args->type != PIPE)
		args = args->prev;
	if (args->type == QUOTE_D)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != QUOTE_D && args->type != PIPE)
		args = args->next;
	if (args && args->type == QUOTE_D)
		count++;
	if (count == 2)
		return (0);
	return (1);
}

int	is_between_quote(t_node	*args)
{
	int	count;

	count = 0;
	if (args->type == QUOTE)
		return (1);
	while (args->prev && args->type != QUOTE && args->type != PIPE)
		args = args->prev;
	if (args->type == QUOTE)
		count++;
	else
		return (1);
	if (args->next)
		args = args->next;
	else
		return (1);
	while (args && args->type != QUOTE && args->type != PIPE)
		args = args->next;
	if (args && args->type == QUOTE)
		count++;
	if (count == 2)
		return (0);
	return (1);
}