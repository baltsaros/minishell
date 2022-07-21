#include "../include/minishell.h"

char	**init_cmd(t_node *args, t_input *data)
{
	int		size;
	int		i;
	char	**str;

	size = get_size_cmd(args);
	if (size == 0)
		return (NULL);
	i = 0;
	str = ms_malloc((size + 1) * sizeof(char *), data);
	while (args && args->type != PIPE)
	{
		if (args->type != QUOTE_D && args->type != QUOTE)
		{
			if (args->type == WORD || args->type == ASTER
				|| args->type == EXECUTABLE || args->type == ENV_VA
				|| args->type == ENV_VA_BR || args->type == ENV_P
				|| args->type == DOLLAR_VAR || args->type == SLASH)
				str[i++] = ms_strdup(args->value, data);
			else if (args->type == EMPTY_ARG)
				str[i++] = ms_strdup("\0", data);
		}
		args = args->next;
	}
	str[i] = NULL;
	return (str);
}