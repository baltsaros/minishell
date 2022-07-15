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

static void	find_files_error(t_input *data, char *str)
{
	write(2, "ls: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	g_status = 1;
	data->node_tmp = ms_token_new(-1, NULL, data);
	ms_token_back(&data->cmds->wild, data->node_tmp);
}

static void	find_files_some(t_input *data, struct dirent *fname
	, char *before, char *after)
{
	while (fname)
	{
		if (!ft_strcmp(fname->d_name, before))
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
	else if (!before && after)
		find_files_error(data, str);
	else if (before)
		find_files_some(data, fname, before, after);
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
		if (ft_strchr(cmds->cmd[i], '*'))
			find_files(data, cmds->cmd[i], fname);
		++i;
	}
	closedir(data->dir);
	ms_token_print(cmds->wild);
}
