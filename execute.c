/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:25 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 18:35:01 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for builtin and execute it if it exists
int	check_builtin(t_input *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmds->cmd[0], data->builtins[i].name))
			++i;
		else
		{
			data->builtins[i].func(data);
			return (1);
		}
	}
	return (0);
}

// fork for all cmds except the last one; dup2 input and output files
void	ms_fork(char *argv[], t_input *data)
{
	int	fd[2];

	error_check(pipe(fd), "", data);
	data->cmds->pid = fork();
	error_check(data->cmds->pid, "", data);
	if (data->cmds->pid == 0)
	{
		if (data->cmds->in_arg)
			error_check(dup2(data->cmds->in, IN),
				data->cmds->in_arg, data);
		if (data->cmds->out_arg && !is_builtin(data, data->cmds))
			error_check(dup2(data->cmds->out, OUT),
				data->cmds->out_arg, data);
		else
			error_check(dup2(fd[1], OUT), "", data);
		close_fds(fd[1], fd[0], 0);
		if (check_builtin(data, data->cmds))
			exit(g_status);
		else
			ms_execve(argv, data);
	}
	close(data->cmds->in);
	error_check(dup2(fd[0], IN), "", data);
	close_fds(fd[1], fd[0], 0);
}

static void	last_cmd(t_input *data)
{
	error_check(dup2(data->cmds->in, IN), "", data);
	error_check(dup2(data->cmds->out, OUT), "", data);
	if (check_builtin(data, data->cmds))
		exit(g_status);
	else
		ms_execve(data->cmds->cmd, data);
	close_fds(data->cmds->in, data->cmds->out, 1);
}

// loop until the last command then execve for the last one
int	pipex(t_input *data)
{
	t_cmd	*head;

	head = data->cmds;
	while (data->cmds->pipe == 1)
	{
		ms_fork(data->cmds->cmd, data);
		data->cmds = data->cmds->next;
	}
	data->cmds->pid = fork();
	if (data->cmds->pid == 0)
		last_cmd(data);
	while (head)
	{
		if (head->next)
		{
			close(0);
			close(1);
		}
		waitpid(head->pid, &g_status, 0);
		if (WIFSIGNALED(data->cmds->pid) && g_status)
			g_status += 128;
		head = head->next;
	}
	exit(g_status);
}

// if there is no pipe or no builtin, execute simple command
// otherwise do pipex or execute builtin (without fork)
int	execute(t_input *data)
{
	if (signal(SIGINT, signal_fork) == SIG_ERR
		|| signal(SIGQUIT, signal_fork) == SIG_ERR)
		error_check(-1, "", data);
	if (data->cmds->pipe == 1 || !check_builtin(data, data->cmds))
	{
		data->pid = fork();
		error_check(data->pid, "", data);
		if (data->pid == 0)
		{
			if (data->cmds->pipe == 1)
				pipex(data);
			else
			{
				set_std(data, data->cmds->in, data->cmds->out);
				ms_execve(data->cmds->cmd, data);
				close_fds(data->cmds->in, data->cmds->out, 1);
			}
		}
		waitpid(data->pid, &g_status, 0);
		if (WIFSIGNALED(data->pid) && g_status)
			g_status += 128;
	}
	return (g_status);
}
