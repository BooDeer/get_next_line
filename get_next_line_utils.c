/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:26:40 by hboudhir          #+#    #+#             */
/*   Updated: 2019/10/31 23:10:25 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
    size_t     i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

char	*ft_strdup(const char *s)
{
    char    *dup;
    int     i;

    i = 0;
    dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
    if (!dup)
        return (NULL);
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    char		*join;
    size_t		n;
    size_t		i;

    if (s1)
    {
		i = 0;
        n = ft_strlen(s1) + ft_strlen(s2);
        join = (char *)malloc((n + 1) * sizeof(char));
        if (!join)
            return (NULL);
        while (i < n)
        {
            if (*s1 != '\0')
                join[i] = *(char *)s1++;
            else if (*s2 != '\0')
                join [i] = *(char *)s2++;
            i++;
        }
        join[i] = '\0';
        return (join);
    }
    return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
