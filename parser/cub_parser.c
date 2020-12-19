#include <fcntl.h>
#include <stdlib.h>
#include "cub_parser.h"

static void	count_objs(t_parser *parser)
{
	int	x;
	int y;
	int num;

	num = 0;
	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (parser->map[y][x] == '2')
				++num;
			++x;
		}
		++y;
	}
	parser->objs_num = num;
}

static void	add_objs_coords(t_parser *parser)
{
	int		x;
	int		y;
	int 	num;

	num = 0;
	y = 0;
	parser->objs = (t_point*)malloc(sizeof(t_point) * parser->objs_num);
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (parser->map[y][x] == '2')
			{
				parser->objs[num].x = x;
				parser->objs[num].y = y;
				++num;
			}
			++x;
		}
		++y;
	}
}

t_parser	*cub_parser(char **argv)
{
	t_parser	*parser;
	int 		fd;

	parser = (t_parser *)malloc(sizeof(t_parser));
	fd = open(argv[1], O_RDONLY);
	settings_parsing(fd, parser);
	map_parsing(parser);
	count_objs(parser);
	add_objs_coords(parser);
	return (parser);
}