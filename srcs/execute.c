#include "../include/minishell.h"

int	check_builtin(t_input *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmds->cmd[0], data->builtins[i].name
				, ft_strlen(data->builtins[i].name) + 1))
			++i;
		else
		{
			data->builtins[i].func(data);
			return (1);
		}
	}
	return (0);
}

void	ft_fork(char *argv[], t_input *data)
{
	int	fd[2];

	error_check(pipe(fd), "In pipe ", 9);
	data->pid = fork();
	error_check(data->pid, "In fork ", 9);
	if (data->pid == 0)
	{
		error_check(dup2(fd[1], STDOUT_FILENO), "In Dup2_ch ", 12);
		if (check_builtin(data, data->cmds))
			exit (data->status);
		else
		{
			close(data->cmds->in);
			close(fd[0]);
			ft_execve(argv, data);
		}
	}
	waitpid(data->pid, NULL, 0);
	error_check(dup2(fd[0], STDIN_FILENO), "In Dup2_pr ", 12);
	close(fd[1]);
}

void	ft_heredoc(char *limiter, t_cmd *elem)
{
	char				*line;

	elem->in = open("heredoc.tmp", O_RDWR | O_CREAT | O_APPEND, 0777);
	error_check(elem->in, "In Open heredoc ", 17);
	while (get_next_line_hd(&line))
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == (ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}	
		write(elem->in, line, ft_strlen(line));
		free(line);
	}
	close(elem->in);
	elem->in = open("heredoc.tmp", O_RDONLY);
	error_check(elem->in, "In Open heredoc ", 17);
	unlink("heredoc.tmp");
}

int	pipex(t_input *data)
{
	error_check(dup2(data->cmds->in, STDIN_FILENO), "In Dup2_inP ", 13);
	while (data->cmds->pipe == 1)
	{
		ft_fork(data->cmds->cmd, data);
		data->cmds = data->cmds->next;
	}
	error_check(dup2(data->cmds->out, STDOUT_FILENO), "In Dup2_outP ", 14);
	if (check_builtin(data, data->cmds))
		exit(data->status);
	else
		ft_execve(data->cmds->cmd, data);
	close(data->cmds->in);
	close(data->cmds->out);
	return (0);
}

void	my_handler(int signo)
{
	printf("Hee hee\n");
	//kill(0, signo);
}

int	execute(t_input *data)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("[ERROR]: SIGNAL HANDLER FAILED!\n");
	if (!data->buf || !*data->buf)
		return (0);
	if (data->cmds->pipe == 1 || !check_builtin(data, data->cmds))
	{
		data->pid = fork();
		if (data->pid == 0)
		{
			// if (signal(SIGINT, SIG_DFL) == SIG_ERR || signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			// 	printf("[ERROR]: SIGNAL HANDLER FAILED!\n");
			signal(SIGINT, my_handler);
			if (data->cmds->pipe == 1)
				pipex(data);
			else
			{
				error_check(dup2(data->cmds->in, STDIN_FILENO),
					"In Dup2_in ", 12);
				error_check(dup2(data->cmds->out, STDOUT_FILENO),
					"In Dup2_out ", 13);
				ft_execve(data->cmds->cmd, data);
			}
		}
		waitpid(data->pid, &data->status, 0);
	}
	//write(1, "\n", 1);
	return (0);
}
