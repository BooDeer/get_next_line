/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:22 by hboudhir          #+#    #+#             */
/*   Updated: 2019/11/08 15:04:47 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t			ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*check_reminder(char *reminder, char **line)
{
	char *p_n;

	p_n = NULL;
	if (reminder)
		if ((p_n = ft_strchr(reminder, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(reminder);
			ft_strcpy(reminder, ++p_n);
		}
		else
		{
			*line = ft_strdup(reminder);
			ft_memset(reminder, 0, ft_strlen(reminder));
		}
	else
		*line = ft_strdup("\0");
	return (p_n);
}

int		check_return(int br, char *reminder, char **line, char *buffer)
{
	if (!br && ft_strlen(reminder) == 0)
		return (0);
	if (br || ft_strlen(reminder) || ft_strlen(*line))
		return (1);
	return (br);
}
int				get_next_line(int fd, char **line)
{
	static char		*reminder;
	char			*buffer;
	int				br;
	char			*p_n;
	char			*tmp;

	if (!fd || !(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	p_n = check_reminder(reminder, line);
	while (!p_n && (br = read(fd, buffer, BUFFER_SIZE)))	
	{	buffer[br] = '\0';
		if ((p_n = ft_strchr(buffer, '\n')))
		{
			*p_n = '\0';
			p_n++;
			reminder = ft_strdup(p_n);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		
	}
	free(buffer);
	return (check_return(br, reminder, line, buffer));
}

int main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("text.txt", O_RDONLY);

	while((i = get_next_line(fd, &line)))
	{
		printf("%d* %s\n", i, line);
		free(line);
	}
		
	printf("%d* %s\n", i, line);
	free(line);

	
	close(fd);
	return (0);
}
