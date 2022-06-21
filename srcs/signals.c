/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:20:14 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/19 21:34:35 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *info, void *context)
{
    // Ctrl + C
	if (signo == SIGINT)
    {
        printf("SIGINT\n");
    }
    // Ctrl + '\'
	else if (signo == SIGQUIT)
    {
        printf("SIGQUIT\n");
    }
		
	(void)signo;
	(void)info;
	(void)context;
}