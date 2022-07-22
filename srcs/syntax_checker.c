/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:37:42 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/21 21:16:54 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_the_next_is_in_arg(t_node *args)
{
	if (args->next->type != IN_ARG)
		return (1);
	return (0);
}

int	is_the_next_is_out_arg(t_node *args)
{
	if (args->next->type != OUT_ARG)
		return (1);
	return (0);
}

int	is_the_next_is_right_type(t_node	*args)
{
	if (args->next->type != WORD && args->next->type != ASTER
		&& args->next->type != ENV_VA && args->next->type != ENV_VA_BR
		&& args->next->type != ENV_P && args->next->type != IN_ARG
		&& args->next->type != OUT_ARG && args->next->type != EXECUTABLE
		&& args->next->type != ENV_BR_EM && args->next->type != ENV_P_EM
		&& args->next->type != EMPTY_ARG)
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
		g_status = 1;
	}
	else if (args->next->type != WORD && args->next->type != ASTER
		&& args->next->type != ENV_VA && args->next->type != ENV_VA_BR
		&& args->next->type != ENV_P && args->next->type != IN_ARG
		&& args->next->type != OUT_ARG && args->next->type != EXECUTABLE
		&& args->next->type != ENV_BR_EM && args->next->type != ENV_P_EM
		&& args->next->type != EMPTY_ARG)
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, args->next->value, ft_strlen(args->value));
		write(2, "'\n", 2);
		g_status = 1;
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
	else if (is_the_next_is_in_arg(args) || is_the_next_is_out_arg(args))
	{
		write(2, "[ERROR]: syntax error near unexpected token `", 45);
		write(2, args->next->value, ft_strlen(args->value));
		write(2, "'\n", 2);
	}
	return (1);
}
