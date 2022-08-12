/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:39:17 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/10 12:55:47 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

// hidden gem
void	*ms_malloc(size_t n, t_input *data)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
	{
		write(2, "YAMSP: ", 7);
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
	dest = ms_malloc(sizeof(char) * (size + 1), data);
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
	tmp = NULL;
}

int	error_check_noexit(int input, char *str, t_input *data)
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
		return (1);
	}
	return (0);
}
