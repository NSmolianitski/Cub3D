#ifndef CUB3D_CUB_PARSER_H
# define CUB3D_CUB_PARSER_H

typedef struct	s_map_size
{
	int			x;
	int			y;
}				t_map_size;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_parser
{
	int			res_x;
	int			res_y;
	char		*n_wall;
	char		*so_wall;
	char		*s_wall;
	char		*w_wall;
	char		*e_wall;
	char		*sprite;
	int			floor_color[3];
	int			ceilling_color[3];
	char		player_dir;
	t_point		player_pos;
	char		**map;
	int			objs_num;
	t_point		*objs;
}				t_parser;

t_parser		*cub_parser(char **argv);
void			settings_parsing(int fd, t_parser *parser);
void			parse_resolution(char *line, t_parser *parser, int i);
void			parse_texture_path(char *line, char **parser, int i);
void			parse_color(char *line, int color[], int i);
void			map_parsing(t_parser *parser);

#endif