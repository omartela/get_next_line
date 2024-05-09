/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:39:06 by omartela          #+#    #+#             */
/*   Updated: 2024/05/09 10:02:35 by omartela         ###   ########.fr       */
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

	b_read = 0;
	while (!check_nl(buffer, b_read) && !check_nl(stash, calc_len(stash)))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(stash);
			return (NULL);
		}
		stash = copy_buffer_to_stash(stash, buffer, b_read);
		if (b_read == 0 || stash == NULL)
		{
			free(stash);
			return (NULL);
		}
	}
	line = extract_line(stash);
	temp_stash = stash;
	stash = ft_strdup(stash + calc_len(line));
	free(temp_stash);
	if (line)
		return (line);
	return (NULL);
}
