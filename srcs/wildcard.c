#include "../include/minishell.h"

static void	find_files_all(t_input *data, t_node *ast, struct dirent *fname)
{
	char *tmp;

	tmp = ms_strdup("", data);
	while (fname)
	{
		tmp = ms_strjoin_free(tmp, fname->d_name, data);
		fname = readdir(data->dir);
		if (fname)
			tmp = ms_strjoin_free(tmp, " ", data);
	}
	if (tmp[0])
	{
		free(ast->value);
		ast->value = tmp;
	}
}

static char	*find_files_some(t_input *data, struct dirent *fname
	, char *before, char *after)
{
	int		len;
	char	*tmp;

	tmp = ms_strdup("", data);
	while (fname)
	{
		len = ft_strlen(before);
		if (!ft_strncmp(fname->d_name, before, len))
		{
			if (!after || (after && ft_strstr(fname->d_name, after)))
			{
				if (tmp[0])
					tmp = ms_strjoin_free(tmp, " ", data);
				tmp = ms_strjoin_free(tmp, fname->d_name, data);
			}
		}
		fname = readdir(data->dir);
	}
	return (tmp);
}

static void find_files_after(t_input *data, struct dirent *fname,
	t_node *ast, char *after)
{
	char	*tmp;

	tmp = ms_strdup("", data);
	while (fname)
	{
		if (ft_strstr(fname->d_name, after))
		{
			if (tmp[0])
				tmp = ms_strjoin_free(tmp, " ", data);
			tmp = ms_strjoin_free(tmp, fname->d_name, data);
		}
		fname = readdir(data->dir);
	}
	if (tmp[0])
	{
		free(ast->value);
		ast->value = tmp;
	}
}

static void	find_files(t_input *data, t_node *ast, struct dirent *fname)
{
	char	*before;
	char	*after;

	data->i = 0;
	before = NULL;
	after = NULL;
	while (ast->value[data->i] != '*')
		data->i++;
	if (data->i > 0)
		before = ms_strndup(ast->value, data->i, data);
	if (ast->value[data->i + 1])
		after = ms_strdup(ast->value + data->i + 1, data);
	if (!before && !after)
		find_files_all(data, ast, fname);
	else if (!before && after)
		find_files_after(data, fname, ast, after);
	else
	{
		data->tmp = find_files_some(data, fname, before, after);
		if (data->tmp[0])
		{
			free(ast->value);
			ast->value = data->tmp;
		}
	}
}

void	asterisks(t_input *data, t_node *ast)
{
	struct dirent	*fname;

	data->dir = opendir(".");
	if (!data->dir)
	{
		write(2, "YAMSP: ", 7);
		perror("opendir");
		g_status = errno;
		exit(errno);
	}
	fname = readdir(data->dir);
	find_files(data, ast, fname);
	closedir(data->dir);
}
