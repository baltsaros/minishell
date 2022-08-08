/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:25 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/09 01:03:59 by abuzdin          ###   ########.fr       */
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

// reads from stdin and saves it in tmp file; stops in case of ctrl+d or ctrl+c
void	ms_heredoc(char *limiter, t_cmd *elem, t_input *data)
{
	char	*line;

	if (signal(SIGINT, signal_hd) == SIG_ERR)
		error_check(-1, "", data);
	elem->in = open("heredoc.tmp", O_RDWR | O_CREAT | O_APPEND, 0777);
	error_check(elem->in, "heredoc", data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		hd_write(data, line, elem->in);
		// ft_putendl_fd(line, elem->in);
		free(line);
	}
	close(elem->in);
	exit(0);
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
		close(fd[0]);
		if (check_builtin(data, data->cmds))
			exit(g_status);
		else
			ms_execve(argv, data);
	}
	close(data->cmds->in);
	error_check(dup2(fd[0], IN), "", data);
	close(fd[1]);
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
	{
		error_check(dup2(data->cmds->in, IN), "", data);
		error_check(dup2(data->cmds->out, OUT), "", data);
		if (check_builtin(data, data->cmds))
			exit(g_status);
		else
			ms_execve(data->cmds->cmd, data);
		close_fds(data->cmds->in, data->cmds->out);
	}
	while(head)
	{
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
				set_std(data, 1, 1);
				ms_execve(data->cmds->cmd, data);
				close_fds(data->cmds->in, data->cmds->out);
			}
		}
		waitpid(data->pid, &g_status, 0);
		if (WIFSIGNALED(data->pid) && g_status)
			g_status += 128;
	}
	return (g_status);
}
