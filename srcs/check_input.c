#include "../include/minishell.h"

static int	read_after_pipe(char **buf, char *msg, char c)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ft_charjoin_free(*buf, '\n');
		*buf = ft_strjoin_free(*buf, tmp);
		if (!ft_strchr(tmp, c))
		{
			free(tmp);
			break;
		}
		free(tmp);
	}
	return (0);
}

static int	read_after(char **buf, char *msg, char c)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ft_charjoin_free(*buf, '\n');
		*buf = ft_strjoin_free(*buf, tmp);
		if (ft_strchr(tmp, c))
		{
			free(tmp);
			break;
		}
		free(tmp);
	}
	return (0);
}

int	check_field(char **buf, t_input *data)
{
	int		quote;
	int		quote_d;
	char	*tmp;

	data->i = 0;
	quote = 0;
	quote_d = 0;
	tmp = *buf;
	while (tmp[data->i])
	{
		if (tmp[data->i] == '\'')
			++quote;
		else if (tmp[data->i] == '\"')
			++quote_d;
		++data->i;
	}
	if (quote && quote % 2 != 0)
		read_after(buf, "quote>", '\'');
	else if (quote_d &&quote_d % 2 != 0)
		read_after(buf, "dquote>", '\"');
	if (tmp[data->i - 1] == '|')
		read_after_pipe(buf, ">", '|');
	return (0);
}
