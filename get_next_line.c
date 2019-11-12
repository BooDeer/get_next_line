/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:22 by hboudhir          #+#    #+#             */
/*   Updated: 2019/11/12 17:39:33 by hboudhir         ###   ########.fr       */
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
			tmp = *line;
			*line = ft_strdup(reminder);
			ft_strcpy(reminder, ++p_n);
			free(tmp);
			free(*buff);
			return (1);
		}
		else
		{
			tmp = *line;
			*line = ft_strdup(reminder);
			ft_memset(reminder, 0, ft_strlen(reminder));
			free(tmp);
			//free(reminder);
		}
	}
	return (0);
}

int				check_return(int br, char *reminder, char **line)
{
	if (!br && !ft_strlen(reminder))
		return (0);
	if (br || ft_strlen(reminder) || ft_strlen(*line))
		return (1);
	return (br);
}

int				get_next_line(int fd, char **line)
{
	static char		*bf;
	char			*rd;
	int				br = 1;
	char			*ptr;
	char			*tmp;

	if (BUFFER_SIZE < 0 || fd < 0 || read(fd, NULL, 0) < 0
	|| !(rd = malloc((BUFFER_SIZE + 1))))
		return (-1);
	if (check_reminder(bf, line, &rd))
		return (1);
	while (br)
	{
		br = read(fd, rd, BUFFER_SIZE);
		rd[br] = '\0';
		if ((ptr = ft_strchr(rd, '\n')))
		{
			*ptr++ = '\0';
			tmp = bf;
			bf = ft_strdup(ptr);
			free(tmp);
			tmp = *line;
			*line = ft_strjoin(*line, rd);
			free(tmp);
			free(rd);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, rd);
		free(tmp);
	}
	free(rd);
	return (check_return(br, bf, line));
}
// int main()
// {
// 	int fd;
// 	char *line;
// 	int i = 0, rd;
// 	fd = open("normal.txt", O_RDONLY);

// 	while ((
// 		rd = get_next_line(fd, &line)
// 	))
// 	{
// 		printf("%d-%d* %s\n", i++,rd , line);
// 		free(line);
// 	}
// 	printf("%d-%d* %s\n", i++, rd, line);
// 	free(line);
// }