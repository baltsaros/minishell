#include "../include/minishell.h"

char	*ft_strndup(char const *str, size_t size)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(*dest) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

int	error_check(int input, char *str, int n, t_input *data)
{
	if (input < 0)
	{
		write(2, "YAMSP-1.6: ", 11);
		write(2, str, n);
		perror("something went wrong");
		data->status = errno;
		exit (errno);
	}
	return (input);
}

void	increase_shlvl(t_input *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "SHLVL", 5))
		i++;
	data->tmp = ft_strdup(data->envp[i] + 6);
	alloc_check_small(data->tmp);
	data->value = ft_strndup(data->envp[i], 6);
	alloc_check_small(data->value);
	data->i = ft_atoi(data->tmp);
	data->i++;
	free(data->tmp);
	data->tmp = ft_itoa(data->i);
	alloc_check_small(data->tmp);
	free(data->envp[i]);
	data->envp[i] = ft_strjoin(data->value, data->tmp);
	alloc_check_small(data->envp[i]);
	free(data->value);
	free(data->tmp);
}

int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	size_f;

	size_f = ft_strlen(to_find);
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (j + 1 == size_f)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_charset(char c, char *charset)
{
	unsigned int	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i])
	{
		if (charset[i] == c)
			return (charset[i]);
		++i;
	}
	return (0);
}
