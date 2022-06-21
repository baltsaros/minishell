#include "../include/minishell.h"

void	find_files(t_input *data)
{

}

void	asterisks(t_input *data)
{
	DIR				*dir;
	t_node			*tmp;
	struct dirent	*fname;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		exit (EXIT_FAILURE);
	}
	data->wild = NULL;
	fname = NULL;
	tmp = data->args;
	while (tmp && tmp->type != ASTER)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if ((!tmp->prev || tmp->prev->type != WORD_AST) 
		&& (!tmp->next || tmp->next->type != WORD_AST))
	{
		while ((fname = readdir(dir)) != NULL)
		{
			data->tmp = ft_strdup(fname->d_name);
			data->node_tmp = ft_token_new(ASTER, data->tmp);
			ft_token_back(&data->wild, data->node_tmp);
		}	
	}
	else if (tmp->prev && tmp->prev->type == WORD_AST)
	{
		while ((fname = readdir(dir)) != NULL)
		{
			if (!ft_strncmp(fname->d_name, tmp->prev->value, ft_strlen(tmp->prev->value)))
			{
				if (!tmp->next || (tmp->next && tmp->next->type == WORD_AST && ft_strstr(fname->d_name, tmp->next->value)))
				{
					data->tmp = ft_strdup(fname->d_name);
					data->node_tmp = ft_token_new(ASTER, data->tmp);
					ft_token_back(&data->wild, data->node_tmp);
				}
			}
		}
	}
	closedir(dir);
	ft_token_print(data->wild);
}