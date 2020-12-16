#ifndef CUB3D_CUB_IMAGE_H
#define CUB3D_CUB_IMAGE_H
#define SCALE 64

#include "cub_parser.h"

typedef struct	s_win
{
	void 		*mlx;
	void 		*win;
	void 		*img;
	char 		*addr;
	int 		bpp;
	int 		ll;
	int 		end;
}				t_win;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_dpoint
{
	double		x;
	double		y;
}				t_dpoint;

typedef struct	s_ray_casting
{
	t_dpoint	delta_dist;
	t_dpoint	ray_dir;
	t_point		step;
	t_point		map;
	t_dpoint	side_dist;
}				t_ray_casting;

typedef struct	s_player
{
	double		x;
	double		y;
	double		pov;
	t_dpoint	dir;
	double		fov_start;
	double		fov_end;
}				t_player;

typedef struct s_color
{
	int 		ceiling;
	int 		floor;
	int			walls;
}				t_color;

typedef struct	s_all
{
	t_dpoint	plane;
	t_player	*plr;
	t_win		*win;
	t_parser	*pr;
}				t_all;

void            fast_mlx_pixel_put(t_win *win, int x, int y, int color);
void			game(t_parser *parser);
int				rgb_to_hex(int arr[3]);
void			draw_scaled_pixel(t_point *map, t_win img, int color);
void			draw_player(t_player *player, t_win img, int color);
void			draw_line(t_dpoint ray_end, int color, t_all *all, int len);
void			draw_wall(t_dpoint start, t_dpoint ray_end, int color, t_all *all, int len);
void			render_next_frame(t_all *all);

#endif
