/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:22 by hboudhir          #+#    #+#             */
/*   Updated: 2019/11/01 18:16:25 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char *check_reminder(char *reminder, char **line)
{
    char *p_n;

    if (reminder)
        if ((p_n = ft_strchr(reminder, '\n')))
        {
            *p_n = '\n';
            *line = ft_strdup(reminder);
			ft_strcpy(reminder, ++p_n);
        }
		else
		{
			*line = ft_strdup(reminder);
			ft_strclr(reminder); // check what function is this = to-check
		}
	else
		*line = ft_strnew(); // to-check
	return (p_n);
}

int		get_next_line(int fd, char **line)
{
	static char		*reminder;
	char			buffer;
	int				br;
	char			*p_n;
	char			*tmp;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	p_n = check_reminder(reminder, line);
	while (!p_n && (br = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[br] = '\0';
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
	return (br || ft_strlen(reminder)) ? 1 : 0;
}


int main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("text.txt", O_RDONLY);

	while(get_next_line(fd, &line))
		printf("* %s\n", line);

	close(fd);
	return (0);
}	