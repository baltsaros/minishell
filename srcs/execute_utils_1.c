/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:18 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/21 16:18:36 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_address(char *cmd[], char *envp[], t_input *data)
{
	char	**env;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		++i;
	envp[i] = ms_strjoin_free(envp[i], ":.", data);
	env = ft_split(envp[i] + 5, ':');
	alloc_check_big(env, data);
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
	if (argv[0][0] == '/')
	{
		data->i = ft_strlen(argv[0]);
		data->j = data->i;
		while (argv[0][data->i] != '/')
			data->i--;
		data->value = ms_strndup(argv[0] + data->i, data->j - data->i, data);
		data->tmp = argv[0];
		argv[0] = data->value;
	}
	else
	{
		if (!ft_strncmp(argv[0], "./minishell", 12))
			increase_shlvl(data);
		data->tmp = access_check(argv, data);
		g_status = 0;
	}
	execve(data->tmp, argv, data->envp);
	free(data->tmp);
	write(2, "YAMSP: ", 7);
	perror("execve error");
	g_status = errno;
	exit(g_status);
}
