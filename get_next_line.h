/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:18:03 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/04 04:19:46 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> //NULL, malloc
# include <unistd.h>

char	*read_line(int fd, char *buf_cont);
char	*new_line(char *buf_cont);
void	delete_newline_from_buffer(char **buf);
char	*get_next_line(int fd);

int		there_is_newline(char *buf_cont);
char	*string_join(char *str1, char *str2);
size_t	ft_strlen_c(const char *str, char c);

#endif