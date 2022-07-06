#include "../include/minishell.h"

char	*get_args(t_node	*args)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (args->type == WORD && args)
	{
		if (args->value[0] != '-')
		{
			str = ft_strjoin_free(str, args->value);
            if (!str)
            {
                free(str);
                return (NULL);
            }
			str = ft_strjoin_free(str, " ");
			if (!str)
			{
				free(str);
				return (NULL);
			}
		}
		if (args->next)
			args = args->next;
		else
			break ;
	}
	return (str);
}
