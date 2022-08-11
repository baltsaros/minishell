/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:39:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/11 13:08:50 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_strndup(char const *str, size_t size, t_input *data)
{
	char	*dest;
	size_t	i;

	dest = ms_malloc((sizeof(char) * (size + 1)), data);
	i = 0;
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

int	error_check(int input, char *str, t_input *data)
{
	size_t	len;

	(void)data;
	if (input < 0)
	{
		write(2, "YAMSP: ", 7);
		len = ft_strlen(str);
		write(2, str, len);
		write(2, ": ", 2);
		perror("");
		g_status = 1;
		ms_free_all(data);
		exit (1);
	}
	return (input);
}

void	increase_shlvl(t_input *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "SHLVL", 5))
		i++;
	if (!data->envp[i])
		return ;
	data->tmp = ms_strdup(data->envp[i] + 6, data);
	data->value = ms_strndup(data->envp[i], 6, data);
	data->i = ft_atoi(data->tmp);
	data->i++;
	free(data->tmp);
	data->tmp = ft_itoa(data->i);
	alloc_check_small(data->tmp, data);
	free(data->envp[i]);
	data->envp[i] = ft_strjoin(data->value, data->tmp);
	alloc_check_small(data->envp[i], data);
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
