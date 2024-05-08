/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:39:06 by omartela          #+#    #+#             */
/*   Updated: 2024/05/08 19:10:29 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

char *copy_buffer_to_str(char *stash, char *buffer, ssize_t btr)
{
	ssize_t i;
	ssize_t j;
	char *temp;

	i = 0;
	j = 0;
	while (stash != NULL && stash[i])
		++i;
	temp = (char *)malloc((i + btr + 1) * sizeof(char));
	if (!temp)
		return NULL;
	while (stash != NULL && stash[j])
	{
		temp[j] = stash[j];
		j++;
	}
	if (!stash)
		free(stash);
	j = 0;
	while (j < btr)
		temp[i++] = buffer[j++];
	temp[i] = '\0';
	return (temp);
}
char *extract_line(char *stash)
{
	char *line;
	int	i;
	int j;

	i = 0;
	j = 0;
	while(stash[i] != '\n' && stash[i] != '\0')
		++i;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j < i)
		line[j++] = *stash++;
	return (line);
}
char *get_next_line(int fd)
{
	static char	*stash;
	char	buffer[BUFFER_SIZE];
	int	bytes_read;

	stash = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (NULL);
	stash = copy_buffer_to_str(stash, buffer, bytes_read);
	return (extract_line(stash));
}

#include <fcntl.h>
#include "get_next_line.h"

int main(void) {
    int fd;
    char *line;

    // Open a file
    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Read lines from the file until end of file
    while ((line = get_next_line(fd)) != NULL) 
	{
		printf("tulostaa rivin\n");
        printf("%s\n", line);
        free(line);
    }

    // Close the file
    close(fd);

    return 0;
}

