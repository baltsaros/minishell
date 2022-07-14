#include "../include/minishell.h"

int	get_next_line(char **line, t_input *data)
{
	char	buf[1];
	ssize_t	r_bytes;

	*line = ft_calloc(1, sizeof(char));
	if (!line | !*line)
		error_check(-1, "In gnl ", 8, data);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(0, buf, 1);
		if (buf[0] == '\"' || buf[0] == '\'')
		{
			*line = ms_charjoin_free(*line, buf[0], data);
			break ;
		}
		*line = ms_charjoin_free(*line, buf[0], data);
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

void	*ms_malloc(size_t n, t_input *data)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
	{
		write(2, "YAMSP-1.6: ", 11);
		write(2, "allocation failed\n", 18);
		ms_free_all(data);
		data->status = 1;
		exit(data->status);
	}
	return (ptr);
}

char	*ms_strdup(const char *s, t_input *data)
{
	char	*dest;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = ms_malloc((sizeof(*s) * (size + 1)), data);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}
