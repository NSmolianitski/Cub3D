#include "cub_parser.h"
#include "cub_utils.h"

static void add_resolution(t_parser *parser, char *width, char *height)
{
	parser->res_x = ft_atoi(width);
	parser->res_y = ft_atoi(height);
	if (parser->res_x > 999999999 || parser->res_y > 999999999)
		print_error("Wrong resolution");
}

void		parse_resolution(char *line, t_parser *parser, int i)
{
	char	width[10];
	char 	height[10];
	int 	j;
	int 	wherr_flag;

	j = 0;
	wherr_flag = 0;
	++i;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!ft_isdigit(line[i]) || wherr_flag > 1)
			print_error("Invalid cub settings");
		if (wherr_flag == 0)
		{
			while (ft_isdigit(line[i]))
				width[j++] = line[i++];
			width[j] = '\0';
			++wherr_flag;
		}
		else if (wherr_flag == 1)
		{
			j = 0;
			while (ft_isdigit(line[i]))
				height[j++] = line[i++];
			height[j] = '\0';
			++wherr_flag;
		}
		i = skip_spaces(line, i);
	}
	add_resolution(parser, width, height);
}