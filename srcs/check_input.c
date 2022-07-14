#include "../include/minishell.h"

static int	check_pipe(char **buf, char *msg, char c, t_input *data)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ms_charjoin_free(*buf, '\n', data);
		*buf = ms_strjoin_free(*buf, tmp, data);
		if (!ft_strchr(tmp, c))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (0);
}

static int	read_after(char **buf, char *msg, char c, t_input *data)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(msg);
		*buf = ms_charjoin_free(*buf, '\n', data);
		*buf = ms_strjoin_free(*buf, tmp, data);
		if (ft_strchr(tmp, c))
		{
			free(tmp);
			break ;
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
		read_after(buf, "quote> ", '\'', data);
	else if (quote_d && quote_d % 2 != 0)
		read_after(buf, "dquote> ", '\"', data);
	if (tmp[data->i - 1] == '|')
		check_pipe(buf, "> ", '|', data);
	return (0);
}

int	is_right_buf(char *buf)
{
	int	i;

	i = 0;
	if (buf[0] == '\0')
		return (1);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
			&& buf[i] != '\v' && buf[i] != '\f' && buf[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
