#include "../include/minishell.h"

void	find_files(t_input *data, t_node *tmp, struct dirent *fname)
{
	if ((!tmp->prev || tmp->prev->type != WORD_AST)
		&& (!tmp->next || tmp->next->type != WORD_AST))
	{
		while (fname)
		{
			data->tmp = ft_strdup(fname->d_name);
			data->node_tmp = ft_token_new(ASTER, data->tmp);
			ft_token_back(&data->wild, data->node_tmp);
			fname = readdir(data->dir);
		}	
	}
	else if (tmp->prev && tmp->prev->type == WORD_AST)
	{
		while (fname)
		{
			if (!ft_strncmp(fname->d_name, tmp->prev->value, ft_strlen(tmp->prev->value)))
			{
				if (!tmp->next || (tmp->next && tmp->next->type == WORD_AST
					&& ft_strstr(fname->d_name, tmp->next->value)))
				{
					data->tmp = ft_strdup(fname->d_name);
					data->node_tmp = ft_token_new(ASTER, data->tmp);
					ft_token_back(&data->wild, data->node_tmp);
				}
			}
			fname = readdir(data->dir);
		}
	}
}

void	asterisks(t_input *data)
{
	t_node			*tmp;
	struct dirent	*fname;

	data->dir = opendir(".");
	if (!data->dir)
	{
		perror("opendir");
		exit (EXIT_FAILURE);
	}
	fname = NULL;
	tmp = data->args;
	while (tmp && tmp->type != ASTER)
		tmp = tmp->next;
	if (!tmp)
		return ;
	fname = readdir(data->dir);
	find_files(data, tmp, fname);
	closedir(data->dir);
	ft_token_print(data->wild);
}
