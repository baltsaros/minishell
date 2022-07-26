/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:43 by abuzdin           #+#    #+#             */
/*   Updated: 2022/07/26 10:45:16 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// update for char** envp
static void	update_envp(t_input *data, char *pwd, char *oldpwd)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "PWD", 3))
		++i;
	if (data->envp[i])
	{
		free(data->envp[i]);
		data->envp[i] = ms_strdup("PWD=", data);
		data->envp[i] = ms_strjoin_free(data->envp[i], pwd, data);
	}
	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD", 3))
		++i;
	if (data->envp[i])
	{
		free(data->envp[i]);
		data->envp[i] = ms_strdup("OLDPWD=", data);
		data->envp[i] = ms_strjoin_free(data->envp[i], oldpwd, data);
	}
	free(pwd);
}

static void	getcwd_error(void)
{
	write(2, "YAMSP: ", 7);
	perror("updating pwd");
	g_status = errno;
	return ;
}

// update for linked lists envp
static void	update_pwd(t_input *data)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (getcwd_error());
	data->envp_tmp = data->envp_n;
	while (data->envp_tmp && ft_strcmp(data->envp_tmp->type, "PWD"))
		data->envp_tmp = data->envp_tmp->next;
	if (data->envp_tmp && !ft_strcmp(data->envp_tmp->type, "PWD"))
	{
		oldpwd = data->envp_tmp->value;
		data->envp_tmp->value = ms_strdup(pwd, data);
	}
	data->envp_tmp = data->envp_n;
	while (data->envp_tmp && ft_strcmp(data->envp_tmp->type, "OLDPWD"))
		data->envp_tmp = data->envp_tmp->next;
	if (data->envp_tmp && !ft_strcmp(data->envp_tmp->type, "OLDPWD"))
	{
		free(data->envp_tmp->value);
		data->envp_tmp->value = oldpwd;
	}
	update_envp(data, pwd, oldpwd);
}

int	yo_cd(t_input *data)
{
	if (!data->cmds->cmd[1])
		return (0);
	else if (chdir(data->cmds->cmd[1]))
	{
		write(2, "YAMSP: ", 7);
		perror("cd");
		g_status = errno;
		return (g_status);
	}
	update_pwd(data);
	return (0);
}
