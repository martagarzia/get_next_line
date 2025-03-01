/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:51 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/01 13:54:34 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_strjoin
		cosa fa:	Concatena le stringhe s1 e s2, 
					allocando dinamicamente una nuova stringa con malloc.
		ritorna:	puntatore alla nuova stringa
						se allocazione ha successo
					NULL
						se allocazione fallisce
*/

#include "get_next_line.h"

/* 
	calcola lunghezza di 2 stringhe con ft_strlen_c
	alloca una stringa grande quanto la somma delle stringhe
	copia il contenunto della str1 in str3
	copia il contenunto della str2 in str3
	aggiunge il carattere di fine stringa
	libera la memoria occupata da str1
	ritrona la nuova str3 che contiene str1 + str2
*/
char	*string_join(char *str1, char *str2)
{
	char	*str3;
	size_t	size1;
	size_t	size2;
	size_t	i;
	size_t	j;
	
	size1 = ft_strlen_c(str1, '\0');
	size2 = ft_strlen_c(str2, '\0');
	i = 0;
	j = 0;
	str3 = (char *)malloc(size1 + size2 + 1);
	if (str3 == NULL)
		return (NULL);
	while (i < size1)
		str3[i++] = str1[j++];
	j = 0;
	while (j < size2)
		str3[i++] = str2[j++];
	str3[i] = '\0';
	free(str1);
	return (str3);
}

/*
	se str è NULL , ritorna 0
	finchè il carattere attuale di buf non è '\0'
	se il carattere
*/
size_t ft_strlen_c(const char *str, char c)
{
    size_t i;

	if (str == NULL)
		return (0);
    i = 0;
    while (str[i] != '\0' && str[i] != c)
        i++;
    return (i);
}
