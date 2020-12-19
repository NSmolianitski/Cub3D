#ifndef CUB3D_CUB_IMAGE_H
#define CUB3D_CUB_IMAGE_H
#define SCALE 20

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
	t_dpoint	dir;
}				t_player;

typedef struct s_color
{
	int 		ceiling;
	int 		floor;
	int			walls;
}				t_color;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_textures
{
	void 		*n_wall;
	t_point		nw_prms;
	void 		*s_wall;
	t_point		sw_prms;
	void 		*w_wall;
	t_point		ww_prms;
	void 		*e_wall;
	t_point		ew_prms;
	void 		*sprite;
	t_point		sprt_prms;
}				t_textures;

typedef struct	s_tex_col
{
	t_win		*wall;
	int			tex_x;
	int 		tex_y;
	double 		tex_step;
	int			wall_side;
	double 		tex_pos;
}				t_tex_col;

typedef struct	s_all
{
	t_dpoint	plane;
	t_player	*plr;
	t_win		*win;
	t_parser	*pr;
	t_textures	*txtrs;
//	t_win		*nw;
//	t_win		*sw;
//	t_win		*ww;
//	t_win		*ew;
//	t_win		*st;
}				t_all;

void            fast_mlx_pixel_put(t_win *win, int x, int y, int color);
void			game(t_parser *parser);
int				rgb_to_hex(int arr[3]);
void			draw_scaled_pixel(t_point *map, t_win img, int color);
void			draw_player(t_player *player, t_win img, int color);
void			draw_line(t_dpoint ray_end, int color, t_all *all, int len);
void			draw_wall(t_dpoint start, t_dpoint ray_end, int color, t_all *all, int len);
void			render_next_frame(t_all *all);
int				get_tex_color(t_win *texture, int x, int y);

#endif
