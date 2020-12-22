#include "cub_utils.h"

void	check_err(int *i, char *line)
{
	int	k;

	k = *i;
	while (line[k] == ' ')
		++k;
	if (line[k] == '\0')
		print_error("Invalid cub settings");
}