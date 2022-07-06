#include "../include/minishell.h"

void	ft_fork(char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;

	error_check(pipe(fd), "In pipe ", 9);
	pid = fork();
	error_check(pid, "In fork ", 9);
	if (pid == 0)
	{
		error_check(dup2(fd[1], STDOUT_FILENO), "In Dup2_ch ", 12);
		close(fd[0]);
		ft_execve(argv, envp);
	}
	waitpid(pid, NULL, 0);
	error_check(dup2(fd[0], STDIN_FILENO), "In Dup2_pr ", 12);
	close(fd[1]);
}

void	ft_heredoc(char *limiter, t_cmd *elem)
{
	char	*line;

	elem->in = open("heredoc.tmp", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (get_next_line_hd(&line))
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0 &&
			ft_strlen(limiter) == (ft_strlen(line) - 1))
		{
			free(line);
			// exit(EXIT_SUCCESS);
			break ;
		}	
		write(elem->in, line, ft_strlen(line));
		free(line);
	}
	elem->in = open("heredoc.tmp", O_RDONLY);
	unlink("heredoc.tmp");
}

// void	ft_heredoc(char *limiter)
// {
// 	char	*line;
// 	int		fd[2];
// 	int		pid1;

// 	error_check(pipe(fd), "In pipe ", 9);
// 	pid1 = fork();
// 	error_check(pid1, "In fork ", 9);
// 	if (pid1 == 0)
// 	{
// 		error_check(dup2(fd[1], STDOUT_FILENO), "In Dup2_ch ", 12);
// 		close(fd[0]);
// 		while (get_next_line_hd(&line))
// 		{
// 			if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0 &&
// 				ft_strlen(limiter) == (ft_strlen(line) - 1))
// 			{
// 				free(line);
// 				exit(EXIT_SUCCESS);
// 			}	
// 			write(1, line, ft_strlen(line));
// 			free(line);
// 		}
// 	}
// 	waitpid(pid1, NULL, 0);
// 	close(fd[1]);
// 	error_check(dup2(fd[0], STDIN_FILENO), "In Dup2_pr ", 12);
// }

int	pipex(t_input *data, t_cmd *cmds)
{
	// if (ft_strncmp("here_doc", argv[1], 9) == 0)
	// {
	// 	i = 3;
	// 	out = ft_open(argv[argc - 1], 0);
	// 	ft_heredoc(argv[2]);
	// }
	// else
	// {
	// 	i = 2;
	// 	in = ft_open(argv[1], 1);
	// 	error_check(dup2(in, STDIN_FILENO), "In Dup2_in ", 12);
	// 	out = ft_open(argv[argc - 1], 2);
	// }
	// if (!cmds->delim)
	// else
	// 	ft_heredoc(cmds->delim);
	error_check(dup2(cmds->in, STDIN_FILENO), "In Dup2_in ", 12);
	while (cmds->pipe == 1){
		ft_fork(cmds->cmd, data->envp);
		cmds = cmds->next;
	}
	// cmds = cmds->next;
	error_check(dup2(cmds->out, STDOUT_FILENO), "In Dup2_out ", 13);
	ft_execve(cmds->cmd, data->envp);
	return (0);
}

int	execute(t_input *data)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;

	while (i < 7)
	{
		if (ft_strncmp(data->argv[0], data->builtins[i].name, ft_strlen(data->builtins[i].name) + 1))
			++i;
		else
		{
			data->builtins[i].func(data);
			break;
		}
	}
	if (i >= 7)
	{
		pid = fork();
		if (pid == 0)
			pipex(data, data->cmds);
			// ft_execve(data->cmds->cmd, data->envp);
	}
	waitpid(pid, &data->status, 0);
	return (0);
}
