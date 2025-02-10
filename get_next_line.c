/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:59 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/10 12:11:11 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	read
		cosa fa:

		ritorna:
	

*/

#include "get_next_line.h"

char	*read_line(int fd, char *buf_cont)
{
	char	*temp;
	int		rdbyte;

	temp = malloc(BUFFER_SIZE + 1);
	if (temp == NULL)
		return (NULL);
	rdbyte = 1;
	while (is_line(buf_cont) == 0 && rdbyte != 0)
	{
		rdbyte = read(fd, temp, BUFFER_SIZE);
		if (rdbyte == -1)
		{
			free(buf_cont);
			free(temp);
			return (NULL);
		}
		temp[rdbyte] = '\0';
		buf_cont = string_join(buf_cont, temp);
	}
	free(temp);
	return (buf_cont);
}

char	*new_line(char *buf_cont)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf_cont[i])
		return (NULL);
	while (buf_cont[i] && buf_cont[i] != '\n')
		i++;
	line = malloc(i + (buf_cont[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buf_cont[i] && buf_cont[i] != '\n')
	{
		line[i] = buf_cont[i];
		i++;
	}
	if (buf_cont[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_buffer(char *buf_cont)
{
	size_t	i;
	size_t	j;
	char	*newbuf;

	i = 0;
	j = 0;
	while (buf_cont[i] && buf_cont[i] != '\n')
		i++;
	if (!buf_cont[i])
	{
		free(buf_cont);
		return (NULL);
	}
	newbuf = malloc(length(buf_cont) - i + 1);
	if (!newbuf)
		return (NULL);
	i++;
	while (buf_cont[i])
		newbuf[j++] = buf_cont[i++];
	newbuf[j] = '\0';
	free(buf_cont);
	return (newbuf);
}

//cambiato buffer in buf_cont
char	*get_next_line(int fd)
{
	static char	*buf_cont = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_cont = read_line(fd, buf_cont);
	if (buf_cont == NULL)
		return (NULL);
	line = new_line(buf_cont);
	buf_cont = new_buffer(buf_cont);
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