/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:38:53 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/11 17:29:21 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signals for main
void	signal_main(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

// signals for forks
void	signal_fork(int signo)
{
	kill(-2, signo);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

// signals for heredoc
void	signal_hd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_status = 130;
	exit(g_status);
}

// signals for unclosed quotes and pipes
void	signal_unclosed(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_status = 1;
	exit(g_status);
}
