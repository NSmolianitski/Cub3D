#include "cub_parser.h"
#include "cub_image.h"

int		main(int argc, char **argv)
{
	t_parser	*parser;

	argc += 0;
	parser = cub_parser(argv);
	game(parser);
	return (0);
}