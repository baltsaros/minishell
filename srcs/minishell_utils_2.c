#include "../include/minishell.h"

int	get_next_line_hd(char **line)
{
	char	buf[1];
	ssize_t	r_bytes;

	*line = ft_calloc(1, sizeof(char));
	if (!line | !*line)
		return (0);
		// error_check(-1, "In gnl ", 8, data);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(0, buf, 1);
		if (buf[0] == '\n')
		{
			*line = ft_charjoin_free(*line, buf[0]);
			alloc_check_small(*line);
			break ;
		}
		*line = ft_charjoin_free(*line, buf[0]);
		alloc_check_small(*line);
	}
	return (r_bytes);
}

int	get_next_line(char **line)
{
	char	buf[1];
	ssize_t	r_bytes;

	*line = ft_calloc(1, sizeof(char));
	if (!line | !*line)
		return (0);
		// error_check(-1, "In gnl ", 8, data);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(0, buf, 1);
		if (buf[0] == '\"' || buf[0] == '\'')
		{
			*line = ft_charjoin_free(*line, buf[0]);
			alloc_check_small(*line);
			break ;
		}
		*line = ft_charjoin_free(*line, buf[0]);
		alloc_check_small(*line);
	}
	return (r_bytes);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}
