#include <stdlib.h>
#include "cub_utils.h"

#define IMS "Not a valid map symbol"
#define ZMP "Zero or more than one player"
#define MNSW "The map is not surrounded by walls"
#define MRN "Malloc returned NULL"
#define ICS "Invalid cub settings"
#define WR "Wrong resolution"
#define WNS "Wrong number of settings"
#define WNA "Wrong number of arguments"
#define ISFF "Invalid settings file format"
#define ICA "Invalid cub argument"
#define ITP "Invalid texture path"
#define WFCC "Wrong floor or ceiling color"

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
	(!cub_strcmp(error, WNA)) ? strprint(WNA, 2) : 0;
	(!cub_strcmp(error, ISFF)) ? strprint(ISFF, 2) : 0;
	(!cub_strcmp(error, ICA)) ? strprint(ICA, 2) : 0;
	(!cub_strcmp(error, ITP)) ? strprint(ITP, 2) : 0;
	(!cub_strcmp(error, WFCC)) ? strprint(WFCC, 2) : 0;
	exit(1);
}