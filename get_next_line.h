/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:18:03 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/01 13:01:38 by mgarzia          ###   ########.fr       */
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
void    buffer_delete_newline(char **buf);
char	*get_next_line(int fd);

int		is_line(char *buf_cont);
char	*string_join(char *str1, char *str2);
size_t	ft_strlen_c(const char *str, char c);

#endif