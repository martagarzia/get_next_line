/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:59 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/04 03:56:32 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 	get_next_line()
		char *get_next_line(int fd);
		
		return (ptr);
		ptr = se restituisce riga
		NULL = EOF, errore (fd invalid)
		
		1. apre fd
		2. legge file e memoriazza dati in un buffer
		3. controlla se in buffer c'è \n
		4. se non c'è \n legge nuovo blocco di file e concatena con vecchio 
			blocco
		4. se trova \n rialloca stringa fino \n in una nuova stringa
		5. cancella stringa estratta dal buffer
		ma conserva tutto dopo \n
		6. restituisce stringa estratta. Altrimenti NULL se EOF o errore
		7. libera risorse

		2. alloca e concatena stringa vecchia e nuova
		3. restituisce ptr a stringa completa


	open()
		int open(const char *pathname, int flags, ...);
		
		int fd = file aperto
		-1 = errore

		1. apre file e gestisce flag
		2. restituisce fd come int

		fcntl.h

	read()
		ssize_t read(int fd, void *buf, size_t count);	
		
		ssize_t byte letti
		0 = EOF
		-1 = errore (fd non valido, errore di sistema)

		1. apre fd
		2. legge stringa dati
		3. restituisce ssize_t byte letti

		unistd.h
	
	printf()
		int printf(const char *format, ...);
		
		int caratteri stampati = se stampa
		-1 = errore

		1. analizza formato e format specifier
		2. sostituisce format specifier
		3. stampa risultato su stdout 

		stdio.h
	
	malloc()
		void *malloc( size_t size );
		
		void *ptr a stringa = se alloca
		NULL = se non alloca
		
		1. richiede memoria al sistema operativo
		2. restituisce puntatore alla memoria allocata

		stdlib.h
	
	argc argv
		int argc =  numero argomenti
		char *argv[] = array di stringhe (i parametri) (char**)
	
	free()
		void free(void *ptr);
		
		1. libera della memoria precedentemente allocata.

		stdlib.h
		
		controlla memoria non liberata (memory leak):
		valgrind --leak-check=full ./gnl

		
*/

#include "get_next_line.h"

/*
	alloca una stringa "temp" grande quanto BUFFER_SIZE + 1 (per \0)
	finchè il carattere attuale di "buf" non è \n
*/
char	*read_line(int fd, char *buf)
{
	char	*temp;
	int		rdbyte;

	rdbyte = 1;
	temp = malloc(BUFFER_SIZE + 1);
	if (temp == NULL)
		return (NULL);
	while (there_is_newline(buf) == 0 && rdbyte != 0)
	{
		rdbyte = read(fd, temp, BUFFER_SIZE);
		if (rdbyte == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		temp[rdbyte] = '\0';
		buf = string_join(buf, temp);
	}
	free(temp);
	return (buf);
}

/*
	(buf[i] == '\n') aggiunge 1 se il carattere attuale è \n.
	può non essere newline se siamo a EOF
*/
char	*new_line(char *buf)
{
	size_t	i;
	char	*line;

	if (buf == NULL || buf[0] == '\0')
		return (NULL);
	i = ft_strlen_c(buf, '\n');
	line = malloc(i + (buf[i] == '\n') + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*
		calcola len caratteri fino a \n, con ft_strlen_c
		alloca (buffer - len + 1) caratteri
		copia caratteri dopo \n nella nuova memoria allocata
		restituisce buffer con solo caratteri dopo \n
*/
void	delete_newline_from_buffer(char **buf)
{
	char	*tmp;
	size_t	len;
	size_t	j;

	tmp = *buf;
	if (tmp == NULL)
		return ;
	len = ft_strlen_c(tmp, '\n');
	if (tmp[len] == '\0')
	{
		free(tmp);
		*buf = NULL;
		return ;
	}
	*buf = malloc(ft_strlen_c(tmp, '\0') - len);
	if (*buf == NULL)
		return ;
	len++;
	j = 0;
	while (tmp[len] != '\0')
		(*buf)[j++] = tmp[len++];
	(*buf)[j] = '\0';
	free(tmp);
}

/*
	leggi e stampa
*/
char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = read_line(fd, buf[fd]);
	if (buf[fd] == NULL)
		return (NULL);
	line = new_line(buf[fd]);
	delete_newline_from_buffer(&buf[fd]);
	return (line);
}

/*
	se il numero di argomenti è 2 (file)
		fd è uguare al ritorno di open()
	se il numero di argomenti è 1 (standard input)
		fd è 0 (terminale)
	se fd -1 vuol dire che c'è stato errore
		interrompe funzione e ritorna 1
	finchè il return di get_next_line() non è NULL
		stampa la stringa (line)
		libera memoria occupata da "line" dopo che l'hai usata
	se gli argomenti erano 2, quindi ha aperto un file, chiudi quel fd
	restituisci 0, per indicare che il programma è andato a buon fine
	
*/
// #include <stdio.h>
// #include <fcntl.h>

// int	main(int argc, char **argv)
// {
// 	char		*line;
// 	int			fd;

// 	/*_apri fd__________________________________________*/
// 	if (argc == 2)
// 		fd = open(argv[1], O_RDONLY); 
// 	else
// 		fd = STDIN_FILENO; 

// 	/*_fail__________________________________________*/
// 	if (fd == -1)
// 	{
// 		perror("Errore nell'apertura del file");
// 		return (1);
// 	}

// 	/*_success__________________________________________*/
// 	printf("fd: %d\n", fd);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("- %s", line);
// 		free(line);
// 	}

// 	if (argc == 2)
// 		close(fd);

// 	return (0);
// }
