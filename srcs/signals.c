/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:38:53 by mthiry            #+#    #+#             */
/*   Updated: 2022/07/20 14:38:55 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_main(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

void	signal_fork(int signo)
{
	kill(-2, signo);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	signal_hd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_status = 130;
	exit(g_status);
}
