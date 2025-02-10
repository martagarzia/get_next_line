/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:51 by mgarzia           #+#    #+#             */
/*   Updated: 2025/02/10 12:28:10 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_line(char *buf_cont)
{
	int	i;

	if (buf_cont == NULL)
		return (0);
	i = 0;
	while (buf_cont[i])
		if (buf_cont[i++] == '\n')
			return (1);
	return (0);
}

size_t	length(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*string_join(char *str1, char *str2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = length(str1);
	len2 = length(str2);
	str = (char *)malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
		str[i++] = str1[j++];
	j = 0;
	while (j < len2)
		str[i++] = str2[j++];
	str[i] = '\0';
	free(str1);
	return (str);
}