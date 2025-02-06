/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:40:55 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/06 16:06:53 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer)
{
	char	*buf;
	int		rdbyte;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	rdbyte = 1;
	while (!check_line(buffer) && rdbyte != 0)
	{
		rdbyte = read(fd, buf, BUFFER_SIZE);
		if (rdbyte == -1)
		{
			free(buffer);
			free(buf);
			return (NULL);
		}
		buf[rdbyte] = '\0';
		buffer = string_join(buffer, buf);
	}
	free(buf);
	return (buffer);
}

char	*new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + (buffer[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*newbuf;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	newbuf = malloc(length(buffer) - i + 1);
	if (!newbuf)
		return (NULL);
	i++;
	while (buffer[i])
		newbuf[j++] = buffer[i++];
	newbuf[j] = '\0';
	free(buffer);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = new_line(buffer);
	buffer = new_buffer(buffer);
	return (line);
}

// Main function is not included in the project.
// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char		*line;
// 	int			fd;
// 	int			i;

// 	fd = open("gnl.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);

// 	i = 1;
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("Line %d: %s\n", i++, line);
// 		free(line);
// 	}
// 	return (0);
// }