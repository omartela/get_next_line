/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:34:36 by omartela          #+#    #+#             */
/*   Updated: 2024/05/10 13:32:15 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*copy_buffer_to_stash(char *stash, char *buffer, ssize_t btr);
char	*extract_line(char *stash);
int		check_nl(char *str, int len);
int		calc_len(char *line);
char	*ft_strdup(const char *src);
char	*free_variable(char *var);

#endif
