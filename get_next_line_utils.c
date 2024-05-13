/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:40:20 by omartela          #+#    #+#             */
/*   Updated: 2024/05/13 12:48:37 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*copy_buffer_to_stash(char *stash, char *buffer, ssize_t btr)
{
	ssize_t		i;
	ssize_t		j;
	char		*temp;

	i = 0;
	j = 0;
	temp = NULL;
	if (btr <= 0)
		return (stash);
	i = calc_len(stash);
	temp = (char *)malloc((i + btr + 1) * sizeof(char));
	if (!temp)
		return (free_variable(stash));
	while (stash != NULL && stash[j])
	{
		temp[j] = stash[j];
		j++;
	}
	j = 0;
	stash = free_variable(stash);
	while (j < btr)
		temp[i++] = buffer[j++];
	temp[i] = 0;
	return (temp);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(stash))
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		++i;
	if (stash[i] == '\n')
		++i;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j < i && stash[j])
	{
		line[j] = stash[j];
		++j;
	}
	line[j] = '\0';
	if (!*line)
		return (free_variable(line));
	return (line);
}

int	check_nl(char *str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (len)
	{
		while (i < len && str[i])
		{
			if (str[i] == '\n')
				return (1);
			++i;
		}
	}
	return (0);
}

int	calc_len(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		++i;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	char	*p;
	size_t	len;

	len = 0;
	if (!src)
		return (NULL);
	while (src != NULL && src[len])
		len++;
	str = malloc(len + 1);
	if (!(str))
		return (0);
	p = str;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (str);
}
