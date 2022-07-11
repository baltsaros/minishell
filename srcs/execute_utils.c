#include "../include/minishell.h"

char	*ft_strjoin_free(char *rest, char *buf)
{
	char	*unis;
	size_t	i;
	size_t	j;

	if (!rest || !buf)
		return (0);
	unis = malloc(sizeof(*unis) * (ft_strlen(rest) + ft_strlen(buf) + 1));
	if (!unis)
		return (0);
	i = 0;
	while (rest[i])
	{
		unis[i] = rest[i];
		++i;
	}
	j = 0;
	while (buf[j])
	{
		unis[i + j] = buf[j];
		++j;
	}
	unis[j + i] = '\0';
	free(rest);
	return (unis);
}

char	*ft_charjoin_free(char *line, char b)
{
	size_t	i;
	char	*unis;

	i = 0;
	while (line[i])
		++i;
	unis = malloc(sizeof(*unis) * (i + 2));
	if (!unis)
		return (0);
	i = 0;
	while (line[i])
	{
		unis[i] = line[i];
		++i;
	}
	unis[i] = b;
	unis[i + 1] = 0;
	free(line);
	return (unis);
}

char	**get_address(char *cmd[], char *envp[])
{
	char	**env;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		++i;
	envp[i] = ft_strjoin(envp[i], ":.");
	env = ft_split(envp[i] + 5, ':');
	alloc_check(env);
	i = 0;
	while (env[i])
	{
		env[i] = ft_strjoin_free(env[i], "/");
		env[i] = ft_strjoin_free(env[i], cmd[0]);
		if (!env[i])
		{
			ft_free(env);
			ft_free(cmd);
			error_check(-1, "In ft_strjoin ", 15);
		}
		++i;
	}
	return (env);
}

char	*access_check(char *cmd[], char *envp[])
{
	char	**env;
	int		i;
	char	*ret;

	env = get_address(cmd, envp);
	i = 1;
	while (access(env[i], X_OK) != 0)
	{
		++i;
		if (!env[i + 1])
			break ;
	}
	if (env[i] && access(env[i], X_OK) < 0)
	{
		write(2, "command not found\n", 19);
		ft_free(env);
		ft_free(cmd);
		exit(127);
	}
	ret = ft_strdup(env[i]);
	if (!ret)
		error_check(-1, "In strdup ", 11);
	ft_free(env);
	return (ret);
}

void	ft_execve(char **argv, t_input *data)
{
	char	*path;

	if (!argv || !argv[0])
	{
		write(2, "parse error near ""\n", 19);
		exit(1);
	}
	if (!ft_strncmp(argv[0], "./minishell", 12))
		increase_shlvl(data);
	path = access_check(argv, data->envp);
	if (execve(path, argv, data->envp) < 0)
	{
		perror("Execve error");
		ft_free(argv);
		free(path);
		exit(127);
	}
}
