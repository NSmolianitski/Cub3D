/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:02:58 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 16:07:31 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub_parser.h"
#include "get_next_line.h"
#include "cub_utils.h"

static int	disgusting_norminette(int *i, char *line)
{
	if (!line[0])
		return (0);
	*i = skip_spaces(line, 0);
	return (1);
}

static int	check_line(char *line, t_parser *parser)
{
	int	i;

	if (!disgusting_norminette(&i, line))
		return (-1);
	if (line[i] == 'R' && line[i + 1] == ' ')
		parse_resolution(line, parser, i);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		parse_texture_path(line, &parser->n_wall, i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		parse_texture_path(line, &parser->s_wall, i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		parse_texture_path(line, &parser->w_wall, i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		parse_texture_path(line, &parser->e_wall, i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		parse_texture_path(line, &parser->sprite, i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		parse_color(line, parser->floor_color, i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		parse_color(line, parser->ceilling_color, i);
	else if (ft_isdigit(line[i]) || line[i] == '\t' || line[i] == ' ')
		return (0);
	else
		print_error("Invalid cub settings");
	return (1);
}

static void	write_lines(int map_fd, char *line)
{
	write(map_fd, line, ft_strlen(line));
	write(map_fd, "\n", 1);
}

void		settings_parsing(int fd, t_parser *parser)
{
	char	*line;
	int		map_fd;
	int		settings_num;

	settings_num = 0;
	while (get_next_line(fd, &line))
	{
		if (!check_line(line, parser))
			break ;
		(line[0] != '\0') ? ++settings_num : 0;
		free(line);
	}
	map_fd = open("./cubs/cube_map.cub", O_TRUNC | O_WRONLY | O_CREAT, 0755);
	write_lines(map_fd, line);
	free(line);
	while (get_next_line(fd, &line))
	{
		write(map_fd, line, ft_strlen(line));
		write(map_fd, "\n", 1);
		free(line);
	}
	write(map_fd, line, ft_strlen(line));
	free(line);
	double_close(fd, map_fd);
	(settings_num != 8) ? print_error("Wrong number of settings") : 0;
}
