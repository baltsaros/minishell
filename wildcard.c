/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:37 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 12:25:37 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_files_all(t_input *data, t_node *ast, struct dirent *fname)
{
	char	*tmp;
	int		check;

	tmp = ms_strdup("", data);
	while (fname)
	{
		check = 0;
		if (fname->d_name[0] != '.')
		{
			tmp = ms_strjoin_free(tmp, fname->d_name, data);
			check = 1;
		}
		fname = readdir(data->dir);
		if (fname && check)
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

static void	find_files_after(t_input *data, struct dirent *fname,
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

// checks for characters before and after *, then act accordingly
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

// open current directory
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
