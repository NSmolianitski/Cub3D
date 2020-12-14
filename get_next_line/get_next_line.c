/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:41:30 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/15 12:41:52 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/get_next_line.h"

static int		buff_prepare(char **buff)
{
	if (BUFFER_SIZE <= 0)
		return (0);
	*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (0 == buff)
		return (0);
	return (1);
}

static void		check_rem(char **rem, char **line)
{
	char	*n_ptr;
	char	*temp;

	if (*rem)
	{
		if ((n_ptr = gnl_strchr(*rem, '\n')))
		{
			*n_ptr = '\0';
			*line = gnl_strdup(*rem);
			temp = *rem;
			*rem = gnl_strdup(++n_ptr);
			free(temp);
		}
		else
		{
			*line = gnl_strdup(*rem);
			free(*rem);
			*rem = 0;
		}
	}
	else
	{
		*line = (char *)malloc(sizeof(char));
		*line[0] = '\0';
	}
}

static int		check_read(char **buff, char **line, char **temp, char **rem)
{
	char	*n_ptr;

	if ((n_ptr = gnl_strchr(*buff, '\n')))
	{
		*n_ptr = '\0';
		*rem = gnl_strdup(++n_ptr);
		*temp = *line;
		*line = gnl_strjoin(*line, *buff);
		free(*temp);
		free(*buff);
		*buff = 0;
		return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*rem = 0;
	int			bytes_red;
	char		*temp;

	if (fd < 0 || !buff_prepare(&buff) || !line)
		return (-1);
	bytes_red = 0;
	check_rem(&rem, line);
	while (!rem && (bytes_red = read(fd, buff, BUFFER_SIZE)))
	{
		if (bytes_red < 0)
			return (-1);
		buff[bytes_red] = '\0';
		if (check_read(&buff, line, &temp, &rem))
			return (1);
		temp = *line;
		*line = gnl_strjoin(*line, buff);
		free(temp);
	}
	free(buff);
	buff = 0;
	if (!bytes_red && !rem)
		return (0);
	return (1);
}
