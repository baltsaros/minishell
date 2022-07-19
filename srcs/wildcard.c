#include "../include/minishell.h"

static void	find_files_all(t_input *data, struct dirent *fname)
{
	while (fname)
	{
		data->tmp = ms_strdup(fname->d_name, data);
		data->node_tmp = ms_token_new(ASTER, data->tmp, data);
		ms_token_back(&data->cmds->wild, data->node_tmp);
		fname = readdir(data->dir);
	}
}

static void	find_files_some(t_input *data, struct dirent *fname
	, char *before, char *after)
{
	int	len;
	
	while (fname)
	{
		len = ft_strlen(before);
		if (!ft_strncmp(fname->d_name, before, len))
		{
			if (!after || (after && ft_strstr(fname->d_name, after)))
			{
				data->tmp = ms_strdup(fname->d_name, data);
				data->node_tmp = ms_token_new(ASTER, data->tmp, data);
				ms_token_back(&data->cmds->wild, data->node_tmp);
			}
		}
		fname = readdir(data->dir);
	}
}

static void	find_files(t_input *data, char *str, struct dirent *fname)
{
	char	*before;
	char	*after;

	data->i = 0;
	before = NULL;
	after = NULL;
	while (str[data->i] != '*')
		data->i++;
	if (data->i > 0)
		before = ms_strndup(str, data->i, data);
	if (str[data->i + 1])
		after = ms_strdup(str + data->i + 1, data);
	if (!before && !after)
		find_files_all(data, fname);
	else if (before && !after)
	{
		data->node_tmp = ms_token_new(-1, NULL, data);
		ms_token_back(&data->cmds->wild, data->node_tmp);
	}
	else if (before)
		find_files_some(data, fname, before, after);
}

static int	check_node(t_input *data, char *str)
{
	t_node *tmp;

	tmp = data->args;
	while (tmp)
	{
		while (tmp->next && tmp->type != ASTER)
			tmp = tmp->next;
		if (tmp && tmp->type == ASTER && !ft_strcmp(tmp->value, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	asterisks(t_input *data, t_cmd *cmds)
{
	struct dirent	*fname;
	size_t			i;

	data->dir = opendir(".");
	data->cmds->wild = NULL;
	if (!data->dir)
	{
		write(2, "YAMSP: ", 7);
		perror("opendir");
		g_status = errno;
		exit(errno);
	}
	i = 0;
	fname = readdir(data->dir);
	while (cmds->cmd[i])
	{
		if (ft_strchr(cmds->cmd[i], '*') && check_node(data, cmds->cmd[i]))
			find_files(data, cmds->cmd[i], fname);
		++i;
	}
	closedir(data->dir);
	ms_token_print(cmds->wild);
}
