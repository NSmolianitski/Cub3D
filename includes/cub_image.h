#ifndef CUB3D_CUB_IMAGE_H
# define CUB3D_CUB_IMAGE_H
# define TEX_W 64
# define TEX_H 64

# include "cub_parser.h"

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			end;
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

typedef struct	s_color
{
	int			ceiling;
	int			floor;
	int			walls;
}				t_color;

typedef struct	s_sprites
{
	double		dist;
	int			order;
}				t_sprites;

typedef struct	s_textures
{
	void		*n_wall;
	t_point		nw_prms;
	void		*s_wall;
	t_point		sw_prms;
	void		*w_wall;
	t_point		ww_prms;
	void		*e_wall;
	t_point		ew_prms;
	void		*sprite;
	t_point		sprt_prms;
}				t_textures;

typedef struct	s_ds
{
	double		x;
	double		y;
	t_point		d_start;
	t_point		d_end;
	t_dpoint	tf;
	int			screen_x;
	int			height;
	int			width;
	double		depth;
}				t_ds;

typedef struct	s_tex_col
{
	t_win		*wall;
	int			tex_x;
	int			tex_y;
	double		tex_step;
	int			wall_side;
	double		tex_pos;
	t_color		clr;
}				t_tex_col;

typedef struct	s_all
{
	t_dpoint	plane;
	t_player	*plr;
	t_win		*win;
	t_parser	*pr;
	t_textures	txtrs;
	t_win		nw;
	t_win		sw;
	t_win		ww;
	t_win		ew;
	t_win		st;
}				t_all;

# pragma pack(push, 1)

typedef struct	s_bmp
{
	short		type;
	int			size;
	short		res;
	short		res2;
	int			offset;
	int			h_size;
	int			width;
	int			height;
	short		planes;
	short		bpp;
	int			compression;
	int			i_size;
	int			ppm_x;
	int			ppm_y;
	int			clrs;
	int			clrs_imp;
}				t_bmp;

# pragma pack(pop)

void			fast_mlx_pixel_put(t_win *win, int x, int y, int color);
void			game(t_parser *parser, int is_save);
int				rgb_to_hex(int arr[3]);
void			render_next_frame(t_all *all, int is_save, int flag);
int				get_tex_color(t_win *texture, int x, int y);
void			sort_sprites(double *dist, int order[], int sprites_num, t_all *all);
void			spr(t_all *all, double z_buff[], t_tex_col tex_col, t_color color);
void			create_bmp(t_all *all);

#endif
