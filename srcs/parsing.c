#include "../include/minishell.h"

int	is_next_elem(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (0);
	if (c == '&')
		return (0);
	return (1);
}

int	get_more_space(char	*buf)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && is_next_elem(buf[i]))
		{
			if (!is_next_elem(buf[i + 1]))
				count++;
		}
		else if (!is_next_elem(buf[i]))
		{
			if (buf[i + 1] != ' ' && is_next_elem(buf[i + 1]))
				count++;
		}
		i++;
	}
	return (count);
}

char	*parse_buf(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *) malloc (((get_more_space(buf) + ft_strlen(buf)) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (buf[i])
	{
		if (buf[i] != ' ' && is_next_elem(buf[i]) && !is_next_elem(buf[i + 1]))
		{
			str[j] = buf[i];
			j++;
			str[j] = ' ';
		}
		else if (buf[i + 1] != ' ' && is_next_elem(buf[i + 1]) && !is_next_elem(buf[i]))
		{
			str[j] = buf[i];
			j++;
			str[j] = ' ';
		}
		else
			str[j] = buf[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(buf);
	return (str);
}

t_cmd	*init_empty_elem(void)
{
	t_cmd	*elem;

	elem = (t_cmd *) malloc (sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->cmd_flags = NULL;
	elem->argument = NULL;
	elem->delim = NULL;
	elem->in = 0;
	elem->out = 1;
	elem->pipe = -1;
	elem->index = 0;
	elem->next = NULL;
	elem->prev = NULL;
	return  (elem);
}

int		get_type(char *str)
{
	if (!ft_strncmp(str, "echo", 4))
 		return(BI_ECHO);
 	if (!ft_strncmp(str, "-n", 2))
 		return(BI_ECHON);
 	if (!ft_strncmp(str, "cd", 2))
 		return(BI_CD);
 	if (!ft_strncmp(str, "pwd", 3))
 		return(BI_PWD);
 	if (!ft_strncmp(str, "export", 6))
 		return(BI_EXPORT);
 	if (!ft_strncmp(str, "unset", 5))
 		return(BI_UNSET);
 	if (!ft_strncmp(str, "env", 3))
 		return(BI_ENV);
 	if (!ft_strncmp(str, "exit", 4))
 		return(BI_EXIT);
 	else
 		return(WORD);
}

t_cmd	*init_elem(char	**line, t_cmd *elem)
{
	int		i;

	i = 0;
	while (line[i] && (line[i][0] != '|' && line[i][1] != '|'))
	{
		if (i == 0)
			elem->cmd = ft_strdup(line[i]);
		else if (line[i][0] == '-')
			elem->cmd_flags = ft_strdup(line[i]);
		else if (get_type(line[i]) == WORD && ft_strncmp(line[i], "<<", 2))
			elem->argument = ft_strdup(line[i]);
		else if (!ft_strncmp(line[i], "<<", 2))
		{
			// Open Heredoc here
			i++;
			elem->delim = ft_strdup(line[i]);
		}
		else if (line[i][0] == '<')
		{
			elem->in = open(elem->argument, O_RDONLY);
			// Basic
		}
		else if (line[i][0] == '>')
		{
			if (line[i][1] == '>')
			{
				elem->out = open(elem->argument, O_WRONLY | O_CREAT | O_APPEND, 00644);
				//Append
			}
			else
			{
				elem->out = open(elem->argument, O_WRONLY | O_CREAT | O_TRUNC, 00644);
				// Basic
			}
		}
		else if (line[i][0] == '|' && line[i][1] != '|')
			elem->pipe = 1;
		i++;
	}
	elem->index = i;
	return (elem);
}

t_cmd	*get_parsed_cmds(char **line)
{
	(void)line;
	t_cmd	*first_elem;
	t_cmd	*arg;
	t_cmd	*new_con;

	first_elem = init_empty_elem();
	if (!first_elem)
		return (NULL);
	first_elem = init_elem(line, first_elem);
	arg = first_elem;
	(void)arg;
	(void)new_con;
	return (first_elem);
}

int	parsing(t_input *data, char *buf)
{
	char	**line;

	buf = parse_buf(buf);
	line = ft_split(buf, ' ');
	free(buf);
	if (!line)
		return (1);

	//for(int i = 0; line[i]; i++)
	//	printf("Line: %s\n", line[i]);

	data->cmds = get_parsed_cmds(line);
	ft_free(line);
	if (!data->cmds)
		return (1);

	for(int i = 0; data->cmds; i++)
	{
		printf("cmd: %s\n", data->cmds->cmd);
		printf("flags: %s\n", data->cmds->cmd_flags);
		printf("argument: %s\n", data->cmds->argument);
		printf("delim: %s\n", data->cmds->delim);
		printf("in: %d\n", data->cmds->in);
		printf("out: %d\n", data->cmds->out);
		printf("pipe: %d\n", data->cmds->pipe);
		printf("index: %d\n", data->cmds->index);
		data->cmds = data->cmds->next;
	}
	return (0);
}