#include <stdlib.h>
#include "cub_utils.h"

#define IMS "Not a valid map symbol"
#define ZMP "Zero or more than one player"
#define MNSW "The map is not surrounded by walls"
#define MRN "Malloc returned NULL"
#define ICS "Invalid cub settings"
#define WR "Wrong resolution"
#define WNS "Wrong number of settings"

void	print_error(char *error)
{
	strprint("Error\n", 2);
	(!cub_strcmp(error, IMS)) ? strprint(IMS, 2) : 0;
	(!cub_strcmp(error, ZMP)) ? strprint(ZMP, 2) : 0;
	(!cub_strcmp(error, MNSW)) ? strprint(MNSW, 2) : 0;
	(!cub_strcmp(error, MRN)) ? strprint(MRN, 2) : 0;
	(!cub_strcmp(error, ICS)) ? strprint(ICS, 2) : 0;
	(!cub_strcmp(error, WR)) ? strprint(WR, 2) : 0;
	(!cub_strcmp(error, WNS)) ? strprint(WNS, 2) : 0;
	exit(1);
}