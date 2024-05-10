/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:39:06 by omartela          #+#    #+#             */
/*   Updated: 2024/05/10 15:59:40 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		buffer[BUFFER_SIZE];
	int			b_read;
	char		*line;
	char		*temp_stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	b_read = 1;
	while (b_read)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
		{
			if (stash && *stash)
			{
				line = extract_line(stash);
				temp_stash = stash;
				stash = ft_strdup(stash + calc_len(line));
				free(temp_stash);
				return (line);
			}
			free(stash);
			return (NULL);
		}
		stash = copy_buffer_to_stash(stash, buffer, b_read);
		if (check_nl(stash, calc_len(stash)))
		{
			line = extract_line(stash);
			temp_stash = stash;
			stash = ft_strdup(stash + calc_len(line));
			free(temp_stash);
			return (line);
		}
	}
	return (NULL);
}
