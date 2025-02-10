/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:18:03 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/10 12:09:35 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> //NULL
# include <unistd.h>

size_t	length(char *str);

int		is_line(char *buf_cont);

char	*get_next_line(int fd);
char	*read_line(int fd, char *buf_cont);
char	*new_line(char *buf_cont);
char	*new_buffer(char *buf_cont);
char	*string_join(char *str1, char *str2);

#endif