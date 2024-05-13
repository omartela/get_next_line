/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:39:06 by omartela          #+#    #+#             */
/*   Updated: 2024/05/13 18:46:19 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*free_variable(char *var)
{
	free(var);
	return (NULL);
}

static char	*rem_line_from_stash(char *stash, char *line)
{
	char	*temp_stash;

	temp_stash = stash;
	stash = ft_strdup(stash + calc_len(line));
	free(temp_stash);
	temp_stash = NULL;
	return (stash);
}

static char	*update_stash(char *stash, char *line)
{
	if (!line)
		stash = free_variable(stash);
	if (line)
		stash = rem_line_from_stash(stash, line);
	return (stash);
}

static char	*get_line(char **stash)
{
	char	*line;

	line = extract_line(*stash);
	*stash = update_stash(*stash, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		b_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	b_read = 1;
	while (b_read)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
		{
			if (b_read == -1)
				stash = free_variable(stash);
			if (stash && *stash)
				return (get_line(&stash));
			stash = free_variable(stash);
			return (NULL);
		}
		stash = copy_buffer_to_stash(stash, buffer, b_read);
		if (check_nl(stash, calc_len(stash)))
			return (get_line(&stash));
	}
	return (NULL);
}
