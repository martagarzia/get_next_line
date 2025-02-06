/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:41:35 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/06 14:41:36 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	length(char *str);

int		check_line(char *buffer);

char	*get_next_line(int fd);
char	*read_line(int fd, char *buffer);
char	*new_line(char *buffer);
char	*new_buffer(char *buffer);
char	*string_join(char *str1, char *str2);

#endif