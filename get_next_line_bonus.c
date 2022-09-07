/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 20:17:45 by acosta            #+#    #+#             */
/*   Updated: 2022/09/07 20:41:29 by acosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = make_new_line(stash[fd]);
	stash[fd] = clean_the_rest(stash[fd]);
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	int		ret;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	ret = 1;
	while (!srch_line_end(stash) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*make_new_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_the_rest(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("panama.papers", O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break;
		free(line);
	}
	close(fd);
	return(0);
}
*/

