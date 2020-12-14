#include <fcntl.h>
#include <stdlib.h>
#include "cub_parser.h"

t_parser	*cub_parser(char **argv)
{
	t_parser	*parser;
	int 		fd;

	parser = (t_parser *)malloc(sizeof(t_parser));
	fd = open(argv[1], O_RDONLY);
	settings_parsing(fd, parser);
	map_parsing(parser);
	return (parser);
}