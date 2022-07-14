#include "../include/minishell.h"

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
		g_status = 1;
		exit(g_status);
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

void	ms_free_node_elems(t_env *tmp)
{
	free(tmp->type);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}
