/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:45 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/20 09:29:46 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
