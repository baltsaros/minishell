#include "../include/minishell.h"

char	*ms_strjoin_free(char *rest, char *buf, t_input *data)
{
	char	*unis;
	size_t	i;
	size_t	j;

	if (!rest || !buf)
		return (0);
	data->i = ft_strlen(rest) + ft_strlen(buf) + 1;
	unis = ms_malloc(sizeof(*unis) * data->i, data);
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

char	*ms_charjoin_free(char *line, char b, t_input *data)
{
	size_t	i;
	char	*unis;

	i = 0;
	while (line[i])
		++i;
	unis = ms_malloc(sizeof(*unis) * (i + 2), data);
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

char	**get_address(char *cmd[], char *envp[], t_input *data)
{
	char	**env;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		++i;
	envp[i] = ms_strjoin_free(envp[i], ":.", data);
	env = ft_split(envp[i] + 5, ':');
	alloc_check(env);
	i = 0;
	while (env[i])
	{
		env[i] = ms_strjoin_free(env[i], "/", data);
		env[i] = ms_strjoin_free(env[i], cmd[0], data);
		++i;
	}
	return (env);
}

char	*access_check(char *cmd[], t_input *data)
{
	char	**env;
	int		i;
	char	*ret;

	env = get_address(cmd, data->envp, data);
	i = 1;
	while (access(env[i], X_OK) != 0)
	{
		++i;
		if (!env[i + 1])
			break ;
	}
	if (env[i] && access(env[i], X_OK) < 0)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		ms_free(env);
		g_status = 127;
		exit(g_status);
	}
	ret = ms_strdup(env[i], data);
	ms_free(env);
	return (ret);
}

void	ms_execve(char **argv, t_input *data)
{
	char	*path;

	if (!argv || !argv[0])
	{
		write(2, "YAMSP: parse error\n", 19);
		exit(1);
	}
	if (!ft_strncmp(argv[0], "./minishell", 12))
		increase_shlvl(data);
	path = access_check(argv, data);
	g_status = 0;
	if (execve(path, argv, data->envp) < 0)
	{
		write(2, "YAMSP: ", 7);
		perror("execve error");
		g_status = errno;
		free(path);
		exit(g_status);
	}
}
