#include "../include/minishell.h"

void	init_all_flags(t_node *elem)
{
	while (elem)
	{
		elem->flag = 0;
		elem = elem->next;
	}
}

int	is_p_closed(t_node *elem)
{
	while (elem)
	{
		if (elem->type == BR_R)
			return (0);
		elem = elem->next;
	}
	return (1);
}

int	add_flags(t_node *elem)
{
	init_all_flags(elem);
	while (elem)
	{
		if (elem->type == QUOTE)
		{
			if (elem->next && elem->next->type != QUOTE)
			{
				elem = elem->next;
				while (elem && elem->type != QUOTE)
				{
					elem->flag = B_QUOTE;
					elem = elem->next;
				}
			}
		}
		else if (elem->type == QUOTE_D)
		{
			if (elem->next && elem->next->type != QUOTE_D)
			{
				elem = elem->next;
				while (elem && elem->type != QUOTE_D)
				{
					elem->flag = B_QUOTE_D;
					elem = elem->next;
				}
			}
		}
		else if (elem->type == BR_L)
		{
			if (elem->next && elem->next->type != BR_R)
			{
				elem = elem->next;
				if (!is_p_closed(elem))
				{
					while (elem && elem->type != BR_R)
					{
						elem->flag = B_QUOTE_P;
						elem = elem->next;
					}
				}
			}
		}
		if (!elem || !elem->next)
			break ;
		elem = elem->next;
	}
	return (0);
}