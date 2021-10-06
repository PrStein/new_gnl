/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:53:16 by sadjigui          #+#    #+#             */
/*   Updated: 2021/06/28 16:09:43 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_return(char **str)
{
	int		i;
	char	*s1;
	char *tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	// if ((*str)[i] != '\n')
	s1 = ft_substr(*str, 0, i + 1);
	// else if ((*str)[i] != '\0')
	// 	s1 = ft_substr(*str, 0, i);

	if ((*str)[i] == '\n')
		tmp = ft_strdup(&(*str)[i + 1]);
	// else if ((*str)[i] == '\0')
	// {
	// 	free(*str);
	// 	free(s1);
	// 	return (NULL);
	// }
	else
		tmp = NULL;
	free(*str);
	*str = tmp;
	if (*str == NULL)
	{
		if(s1)
			free(s1);
		free(*str);
		return (NULL);
	}
	return (s1);
}

static int	find_line(int fd, char **line, char **buf)
{
	int		i;
	char	*str;

	i = 1;
	while (i > 0)
	{
		i = read(fd, *buf, BUFFER_SIZE);
		buf[0][i] = '\0';
		if (!*line || !**line)
			str = ft_strdup(*buf);
		else
			str = ft_strjoin(*line, *buf);
		free(*line);
		*line = str;
		if (ft_check (*line, '\n') || ft_check (*line, '\0'))
			break ;
	}
	free (*buf);
	return (i);
}

char	*get_next_line(int fd)
{
	char	*buf/*[BUFFER_SIZE + 1]*/;
	int	i;
	static char	*str;

	if (fd < 1 || BUFFER_SIZE < 1 || read(fd, "", 0) == -1)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	i = find_line(fd, &str, &buf);
	// if (i < 0)
	// {
	// 	free(str);
	// 	return (NULL);
	// }
	return (find_return(&str));
}
