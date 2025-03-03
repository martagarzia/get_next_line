/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:59 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/04 00:46:49 by mgarzia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
        get_next_line -------------------------------------------------------------
                cosa fa:        legge una riga alla volta (terminata da \n o EOF) 
                                        da un file descriptor.
                ritorna:        puntatore a una stringa allocata dinamicamente
                                          -     se viene letta una riga completa
                                        NULL
                                          -     se raggiunge EOF senza dati residui
                                          -     se c'è un errore o il file descriptor è invalido
                                        ND
                                          -     se il file puntato dal file descriptor (fd) 
                                                cambia durante l'esecuzione
                                          -     se la funzione read 
                                                non ha ancora raggiunto la fine del file (EOF)
                                          -     se legge un file binario 
                                                (immagini, eseguibili, dati binari)
        read ----------------------------------------------------------------------
                prototipo:      ssize_t read(int fd, void *buf, size_t count);
                cosa fa:        legge dati
                                        da un file o 
                                        da un dispositivo identificato da un file descriptor (fd)
                                        e li memorizza in un buffer (buf) fornito dall'utente, 
                                        fino a un massimo di count byte.
                ritorna:        numero di byte letti
                                                se ha successo. 
                                                = count:        lettura completa dei byte richiesti.
                                                < count:        fine del file raggiunta o 
                                                                        meno dati disponibili.
                                        0
                                                se raggiunge EOF senza leggere nulla.
                                        -1
                                                se fallisce.
                                                e imposta errno per indicare il tipo di errore
                                                (es. EBADF, EFAULT, ecc.).
        malloc --------------------------------------------------------------------
                prototipo:      void *malloc( size_t size );
                cosa fa:        alloca dinamicamente un blocco di memoria 
                                        di dimensione specificata in byte 
                                        nello heap
                ritorna:        puntatore (void *) al primo byte del blocco allocato
                                                se alloca
                                        NULL
                                                se non alloca
        ___________________________________________________________________________
        
        puntatore (char *residual)
                cambia il valore di `residual` nella funzione attuale
        puntatore a puntatore (char **residual) 
                cambia il valore del puntatore originale
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
	while (is_line(buf) == 0 && rdbyte != 0)
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
void delete_newline_from_buffer(char **buf)
{
    char    *tmp;
    size_t  len;
    size_t  j;

    tmp = *buf;
    if (tmp == NULL)
        return;
    len = ft_strlen_c(tmp, '\n');
    if (tmp[len] == '\0')
    {
        free(tmp);
        *buf = NULL;
        return;
    }
    *buf = malloc(ft_strlen_c(tmp, '\0') - len);
    if (*buf == NULL)
        return;
    len++;
    j = 0;
    while (tmp[len] != '\0')
        (*buf)[j++] = tmp[len++];
    (*buf)[j] = '\0';
    free(tmp);
}
/*
leggi
*/
char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/*_1____________________________*/
	buf = read_line(fd, buf);
	if (buf == NULL)
		return (NULL);
	/*_2____________________________*/
	line = new_line(buf);
	/*_3____________________________*/
	delete_newline_from_buffer(&buf);
	return (line);
}
/* -gdwarf-4 */

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
