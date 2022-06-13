/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:56 by acosta            #+#    #+#             */
/*   Updated: 2022/06/13 18:11:59 by acosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	ligne[4];
	
	read(fd, ligne, BUFFER_SIZE);
//premiere partie qui renvoie une ligne jusqu'au retour
	//lire la ligne jusqu'a la fin
	//l'enregistrer, la retourner
	return(&ligne);
}


#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*str;

	fd = open("panama.papers", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
//	free(str);
//	str = get_next_line(fd);
//	printf("%s", str);
	close(fd);
	return(0);
}


