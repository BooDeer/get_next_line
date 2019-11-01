/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:22 by hboudhir          #+#    #+#             */
/*   Updated: 2019/11/01 17:21:12 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	int				chr;
	int				k;
	char			*ptr;
	char			*buffer;
	static char		*extra;
	
	k = 1;
	*line = ft_strdup("");
	if (extra)
		*line = ft_strjoin(*line, extra);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	while (k && (chr = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[chr] = '\0';
        if ((ptr = ft_strchr(buffer, '\n')))
        {
            extra = ft_strdup(ptr + 1);
			*ptr = '\0'; 
            k = 0;
        } 
        *line = ft_strjoin(*line ,buffer);

	}
	return (1);
}


int main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("text.txt", O_RDONLY);

	get_next_line(fd, &line);
	printf("* %s\n", line);
	get_next_line(fd, &line);
	printf("* %s\n", line);
	get_next_line(fd, &line);
	printf("* %s\n", line);
	get_next_line(fd, &line);
	printf("* %s\n", line);	
	close(fd);
	return (0);
}	