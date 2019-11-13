/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:22 by hboudhir          #+#    #+#             */
/*   Updated: 2019/11/13 16:21:18 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int			check_reminder(char *reminder, char **line, char **buff)
{
	char *p_n;
	char *tmp;

	p_n = NULL;
	*line = ft_strdup("");
	if (reminder)
	{
		if ((p_n = ft_strchr(reminder, '\n')))
		{
			*p_n = '\0';
			free(*line);
			*line = ft_strdup(reminder);
			ft_strcpy(reminder, ++p_n);
			free(*buff);
			return (1);
		}
		else
		{
			tmp = *line;
			*line = ft_strdup(reminder);
			ft_memset(reminder, 0, ft_strlen(reminder));
			free(tmp);
		}
	}
	return (0);
}

int			check_return(int br, char *reminder, char **line)
{
	if (!br && !ft_strlen(reminder))
		return (0);
	if (br || ft_strlen(reminder) || ft_strlen(*line))
		return (1);
	return (br);
}

void		get_next_line2(char *ptr, char **remind, char ***line, char **buf)
{
	char	*tmp;

	*ptr++ = '\0';
	tmp = *remind;
	*remind = ft_strdup(ptr);
	free(tmp);
	tmp = **line;
	**line = ft_strjoin(**line, *buf);
	free(tmp);
	free(*buf);
}

int			get_next_line(int fd, char **line)
{
	static char		*reminder;
	char			*buffer;
	int				br;
	char			*ptr;
	char			*tmp;

	if (BUFFER_SIZE < 0 || fd < 0 || read(fd, NULL, 0) < 0
	|| !(buffer = malloc((BUFFER_SIZE + 1))))
		return (-1);
	if (check_reminder(reminder, line, &buffer))
		return (1);
	while ((br = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[br] = '\0';
		if ((ptr = ft_strchr(buffer, '\n')))
		{
			get_next_line2(ptr, &reminder, &line, &buffer);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	free(buffer);
	return (check_return(br, reminder, line));
}
