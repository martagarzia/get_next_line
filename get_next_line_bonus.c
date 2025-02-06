/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:41:52 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/06 16:06:40 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buff[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buff[fd] = read_line(fd, buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	line = new_line(buff[fd]);
	buff[fd] = new_buffer(buff[fd]);
	return (line);
}

// Main function is not included in the project.
// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char		*line;
// 	int			fd1, fd2, fd3;
// 	int			i, j, k;


// 	fd1 = open("gnlbonus1.txt", O_RDONLY);
// 	fd2 = open("gnlbonus2.txt", O_RDONLY);
// 	fd3 = open("gnlbonus3.txt", O_RDONLY);

// 	i = 1;
// 	j = 1;
// 	k = 1;
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 		return (1);

// 	while ((line = get_next_line(fd1)) != NULL)
// 	{
// 		printf("File 1 - Line %d: %s\n", i++, line);
// 		free(line);
// 	}
// 	printf("\n");
// 	while ((line = get_next_line(fd2)) != NULL)
// 	{
// 		printf("File 2 - Line %d: %s\n", j++, line);
// 		free(line);
// 	}
// 	printf("\n");
// 	while ((line = get_next_line(fd3)) != NULL)
// 	{
// 		printf("File 3 - Line %d: %s\n", k++, line);
// 		free(line);
// 	}
// 	return (0);
// }