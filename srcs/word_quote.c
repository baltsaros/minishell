#include "../include/minishell.h"

int word_quote_fusion(t_node *elem, t_input *data)
{
	t_node	*first;
	int		type;

	while (elem && elem->type != QUOTE && elem->type != QUOTE_D)
		elem = elem->next;
	if (elem)
		type = elem->type;
	else if (!elem)
		return (0);
	if (elem->next && elem->next->type != type)
		first = elem->next;
	else
		return (0);
	if (elem->prev && elem->prev->type == WORD)
	{
		first->value = ft_strjoin(elem->prev->value, first->value);
		// elem = ms_token_del(elem->prev);
		elem->prev->type = 0;

	}
	elem = elem->next->next;
	while (elem && elem->type != type)
	{
		first->value = ms_strjoin_free(first->value, elem->value, data);
		elem = ms_token_del(elem);
	}
	if (elem->next && elem->next->type == WORD)
	{
		first->value = ms_strjoin_free(first->value, elem->next->value, data);
		ms_token_del(elem->next);
	}
	// printf("elem type is %d, value is %s\n", elem->type, elem->value);
	return (0);
}

// int word_quote_fusion(t_node *elem, t_input *data)
// {
//     while (elem)
//     {
//         printf("Readed: %s\n", elem->value);
//         if (!is_between_d_quote(elem))
//         {
//             if (elem->next && elem->next->type == QUOTE_D)
//             {
//                 if (elem->next->next && elem->next->next->type != WSPACE)
//                 {
//                     elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
//                     if (!elem->value)
//                         return (1);
//                     // elem->next = update_next_and_prev(elem->next);
//                     elem = ms_token_del(elem->next->next);
//                 }
//             }
//             if (elem->prev && elem->prev->type == QUOTE_D)
//             {
//                 if (elem->prev->prev && elem->prev->prev->type != WSPACE)
//                 {
//                     elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
//                     if (!elem->value)
//                         return (1);
//                     // elem->prev = update_prev_and_next(elem->prev);
//                     elem = ms_token_del(elem->prev->prev);
//                 }
//             }
//         }
//         if (!is_between_quote(elem))
//         {
//             if (elem->next && elem->next->type == QUOTE)
//             {
//                 if (elem->next->next && elem->next->next->type != WSPACE)
//                 {
//                     elem->value = ms_strjoin_free(elem->value, elem->next->next->value, data);
//                     if (!elem->value)
//                         return (1);
//                     // elem->next = update_next_and_prev(elem->next);
//                     elem = ms_token_del(elem->next->next);
//                 }
//             }
//             // if (elem->prev && elem->prev->type == QUOTE)
//             // {
//             //     if (elem->prev->prev && elem->prev->prev->type != WSPACE)
//             //     {
//             //         elem->value = ms_strjoin_free(elem->prev->prev->value, elem->value, data);
//             //         if (!elem->value)
//             //             return (1);
//             //         elem->prev = update_prev_and_next(elem->prev);
//             //     }
//             // }
//         }

//         // if (!elem->next)
//         //     break ;
//         elem = elem->next;
//     }
//     return (0);
// }
