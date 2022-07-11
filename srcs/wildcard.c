#include "../include/minishell.h"

static void	find_files_all(t_input *data, struct dirent *fname)
{
	while (fname)
	{
		data->tmp = ft_strdup(fname->d_name);
		data->node_tmp = ft_token_new(ASTER, data->tmp);
		ft_token_back(&data->cmds->wild, data->node_tmp);
		fname = readdir(data->dir);
	}
}

static void	find_files_error(t_input *data, char *str)
{
	write(2, "ls: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	data->node_tmp = ft_token_new(-1, NULL);
	ft_token_back(&data->cmds->wild, data->node_tmp);
}

static void	find_files_some(t_input *data, struct dirent *fname
	, char *before, char *after)
{
	while (fname)
	{
		if (!ft_strncmp(fname->d_name, before, ft_strlen(before)))
		{
			if (!after || (after && ft_strstr(fname->d_name, after)))
			{
				data->tmp = ft_strdup(fname->d_name);
				data->node_tmp = ft_token_new(ASTER, data->tmp);
				ft_token_back(&data->cmds->wild, data->node_tmp);
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
		before = ft_strndup(str, data->i);
	if (str[data->i + 1])
		after = ft_strdup(str + data->i + 1);
	if (!before && !after)
		find_files_all(data, fname);
	else if (!before && after)
		find_files_error(data, str);
	else if (before)
		find_files_some(data, fname, before, after);
}

void	asterisks(t_input *data)
{
	struct dirent	*fname;
	size_t			i;

	data->dir = opendir(".");
	data->cmds->wild = NULL;
	if (!data->dir)
	{
		perror("opendir");
		exit (EXIT_FAILURE);
	}
	i = 0;
	fname = readdir(data->dir);
	while (data->cmds->cmd[i])
	{
		if (ft_strchr(data->cmds->cmd[i], '*'))
			find_files(data, data->cmds->cmd[i], fname);
		++i;
	}
	closedir(data->dir);
	ft_token_print(data->cmds->wild);
}
