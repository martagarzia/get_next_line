/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarzia <mgarzia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:59 by mgarzia           #+#    #+#             */
/*   Updated: 2025/03/01 11:24:23 by mgarzia          ###   ########.fr       */
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

char	*read_line(int fd, char *buf_cont)
{
	char	*temp;
	int		rdbyte;

	rdbyte = 1;
	temp = malloc(BUFFER_SIZE + 1);
	if (temp == NULL)
		return (NULL);
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
	size_t	i;
	char	*line;

	i = 0;
	if (buf_cont[i] == '\0')
		return (NULL);
	while (buf_cont[i] != '\0' && buf_cont[i] != '\n')
		i++;
	line = malloc(i + (buf_cont[i] == '\n') + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buf_cont[i] != '\0' && buf_cont[i] != '\n')
	{
		line[i] = buf_cont[i];
		i++;
	}
	if (buf_cont[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*
        calcola len caratteri fino a \n
        alloca (buffer - len + 1) caratteri
        copia caratteri dopo \n nella nuova memoria allocata
        restituisce buffer con solo caratteri dopo \n
*/

void buffer_delete_newline(char **buf)
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


/* calcola size_t caratteri fino a \n*/
size_t ft_strlen_c(const char *str, char c)
{
    size_t i;

    i = 0;
    while (str[i] != '\0' && str[i] != c)
        i++;
    return (i);
}


char	*get_next_line(int fd)
{
	static char	*buf_cont;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_cont = read_line(fd, buf_cont);
	if (buf_cont == NULL)
		return (NULL);
	line = new_line(buf_cont);
	buffer_delete_newline(&buf_cont);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(int argc, char **argv)
// {
// 	char		*line;
// 	int			fd;

// 	if (argc == 2)
// 		fd = open(argv[1], O_RDONLY); 
// 	else
// 		fd = STDIN_FILENO; 

// 	if (fd == -1)
// 	{
// 		perror("Errore nell'apertura del file");
// 		return (1);
// 	}

// 	printf("fd: %d\n", fd);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("- %s", line);
// 		free(line);
// 	}
	
// 	if (argc == 2)
// 		close(fd);

// 	return (0);
// }
