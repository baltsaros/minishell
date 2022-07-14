#include "../include/minishell.h"

static size_t	check_str(char const *s, char *charset)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && check_charset(s[i], charset))
			++i;
		if (s[i])
			++n;
		if (s[i] == '"' || s[i] == '\'')
		{
			++i;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				++i;
		}
		while (s[i] && !(check_charset(s[i], charset)))
			++i;
	}
	return (n);
}

static void	find_end(char const *s, size_t *start, size_t *end, char *charset)
{
	while (s[*start + *end] && check_charset(s[*start + *end], charset))
		++start;
	while (s[*start + *end] && !check_charset(s[*start + *end], charset)
		&& s[*start + *end] != '"' && s[*start + *end] != '\'')
		++(*end);
	if (s[*start + *end] && (s[*start + *end] == '"'
			|| s[*start + *end] == '\''))
	{
		++(*end);
		while (s[*start + *end] && s[*start + *end] != '"'
			&& s[*start + *end] != '\'')
			++(*end);
		++(*end);
	}
}

static char	**ms_create_str(char **spl, char const *s, int i, char *cset,
	t_input *data)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start])
	{
		end = 0;
		find_end(s, &start, &end, cset);
		if (end > 0)
		{
			spl[i] = ms_strndup(s + start, end, data);
			++i;
			start = start + end;
		}
	}
	spl[i] = NULL;
	return (spl);
}

char	**ms_split_space(char const *s, char *cset, t_input *data)
{
	char	**spl;
	size_t	size;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	size = check_str(s, cset);
	spl = ms_malloc((sizeof(*spl) * (size + 1)), data);
	spl = ms_create_str(spl, s, i, cset, data);
	return (spl);
}
