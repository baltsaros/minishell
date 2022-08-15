/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:05 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/15 10:18:14 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creation of envp variable in linked list form
static void	create_envp(t_input *data, char *envp[])
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (envp[i])
	{
		start = 0;
		end = 0;
		while (envp[i][start] != '=')
			++start;
		while (envp[i][end])
			++end;
		data->type = ms_strndup(envp[i], start, data);
		data->value = ms_strndup(envp[i] + start + 1, end - start - 1, data);
		data->envp_tmp = ms_envp_new(data->type, data->value, data);
		ms_envp_back(&data->envp_n, data->envp_tmp);
		++i;
	}
	data->envp_len = i;
}

void	strdup_and_increase(t_input *data, char **tmp, char *type)
{
		tmp[data->i] = ft_strjoin(type, data->tmp);
		alloc_check_small(tmp[data->i], data);
		data->i++;
}

static void	add_missed_envp(t_input *data, int *vars)
{
	int		size;
	char	**tmp;

	size = data->i + vars[0] + vars[1] + vars[2];
	tmp = ms_malloc((sizeof(*tmp) * size), data);
	data->i = 0;
	while (data->envp[data->i])
	{
		tmp[data->i] = ms_strdup(data->envp[data->i], data);
		data->i++;
	}
	data->tmp = getcwd(NULL, 0);
	if (!data->tmp)
	{
		write(2, "YAMSP: ", 7);
		perror("pwd");
		ms_free_all(data);
		exit(1);
	}
	if (vars[0])
		strdup_and_increase(data, tmp, "HOME=");
	if (vars[1])
		strdup_and_increase(data, tmp, "PWD=");
	if (vars[2])
		strdup_and_increase(data, tmp, "OLDPWD=");
	tmp[data->i] = NULL;
	ms_free(data->envp);
	data->envp = tmp;
	free(data->tmp);
}

// creation of envp variable in char** form
// also checks for missing envp like HOME, PWD, OLDPWD
static void	copy_envp(t_input *data, char *envp[])
{
	int	size;
	int	vars[3];

	size = 0;
	vars[0] = 1;
	vars[1] = 1;
	vars[2] = 1;
	while (envp[size])
		++size;
	data->envp = ms_malloc((sizeof(*data->envp) * (size + 1)), data);
	data->i = 0;
	while (envp[data->i])
	{
		if (!ft_strncmp(envp[data->i], "HOME", 4))
			vars[0] = 0;
		else if (!ft_strncmp(envp[data->i], "PWD", 3))
			vars[1] = 0;
		if (!ft_strncmp(envp[data->i], "OLDPWD", 6))
			vars[2] = 0;
		data->envp[data->i] = ms_strdup(envp[data->i], data);
		data->i++;
	}
	data->envp[data->i] = NULL;
	add_missed_envp(data, vars);
}

void	envp_init(t_input *data, char *envp[])
{
	static struct s_builtin	builtins[] = {
	{"pwd", &yo_pwd},
	{"cd", &yo_cd},
	{"echo", &yo_echo},
	{"export", &yo_export},
	{"env", &yo_env},
	{"unset", &yo_unset},
	{"exit", &yo_exit}};

	copy_envp(data, envp);
	data->envp_n = NULL;
	data->type = NULL;
	data->value = NULL;
	data->tmp = NULL;
	data->i = 0;
	data->j = 0;
	data->envp_tmp = NULL;
	data->node_tmp = NULL;
	data->builtins = builtins;
	create_envp(data, data->envp);
}

void	data_init(t_input *data)
{
	data->args = NULL;
	data->exec = 1;
	tokenization(data);
	data->argc = ms_token_size(data->args);
	if (data->argc == 1 && !ft_strcmp(data->buf, "secret"))
	{
		free(data->prompt);
		data->prompt = ms_strdup("🌞 YAMSP-1.7 🌞 $ ", data);
		secret_mode();
	}
	else if (data->argc == 1 && !ft_strcmp(data->buf, "uwu"))
	{
		free(data->prompt);
		data->prompt = ms_strdup("😽 YAMSP-UwU 😽 $ ", data);
		uwu_mode();
	}
	else if (data->argc == 1 && !ft_strcmp(data->buf, "normal"))
	{
		free(data->prompt);
		data->prompt = ms_strdup("YAMSP-1.6$ ", data);
		normal_mode();
	}
}
