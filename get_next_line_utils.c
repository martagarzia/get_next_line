/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:51 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/01 11:24:33 by mgarzia          ###   ########.fr       */
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

/* Controlla se nel buffer è presente un carattere newline (\n), 
indicando che una riga completa può essere estratta. */
// line_complete
int	is_line(char *buf_cont)
{
	int	i;

	i = 0;
	if (buf_cont == NULL)
		return (0);
	while (buf_cont[i] != '\0')
	{
		if (buf_cont[i++] == '\n')
			return (1);
	}
	return (0);
}

/* Concatena due stringhe, 
alloca una nuova stringa con il contenuto combinato 
e libera la memoria della prima stringa (str1). */
char	*string_join(char *str1, char *str2)
{
	char	*str3;
	size_t	size1;
	size_t	size2;
	size_t	i;
	size_t	j;
	
	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
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

/* Calcola e restituisce la lunghezza di una stringa, 
restituendo 0 se la stringa è NULL. */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
		i++;
	return (i);
}