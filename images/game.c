/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:49:07 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:56:07 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"

void		render_next_frame(t_all *all, int is_save, int flag)
{
	t_color color;

	if (flag)
		all->win->win = mlx_new_window(all->win->mlx, all->pr->res_x,
				all->pr->res_y, "Cub3D");
	mlx_clear_window(all->win->mlx, all->win->win);
	color.ceiling = rgb_to_hex(all->pr->ceilling_color);
	color.floor = rgb_to_hex(all->pr->floor_color);
	color.walls = 0x0104d3e;
	draw_screen(all, 0x0889bba);
	ray_casting(all, color);
	if (is_save)
	{
		create_bmp(all);
		exit(0);
	}
	else
		mlx_put_image_to_window(all->win->mlx,
				all->win->win, all->win->img, 0, 0);
}

static void	fill_txtrs(t_all *all, t_parser *parser)
{
	all->txtrs.n_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall,
			&all->txtrs.nw_prms.x, &all->txtrs.nw_prms.y);
	all->txtrs.s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->so_wall,
			&all->txtrs.sw_prms.x, &all->txtrs.sw_prms.y);
	all->txtrs.s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->s_wall,
			&all->txtrs.sw_prms.x, &all->txtrs.sw_prms.y);
	all->txtrs.w_wall = mlx_xpm_file_to_image(all->win->mlx, parser->w_wall,
			&all->txtrs.ww_prms.x, &all->txtrs.ww_prms.y);
	all->txtrs.e_wall = mlx_xpm_file_to_image(all->win->mlx, parser->e_wall,
			&all->txtrs.ew_prms.x, &all->txtrs.ew_prms.y);
	all->txtrs.sprite = mlx_xpm_file_to_image(all->win->mlx, parser->sprite,
			&all->txtrs.sprt_prms.x, &all->txtrs.sprt_prms.y);
}

static void	prepare_struct(t_all *all, t_win *win,
		t_player *player, t_parser *parser)
{
	all->win = win;
	all->plr = player;
	all->pr = parser;
	all->plr->y = parser->player_pos.y + 0.5;
	all->plr->x = parser->player_pos.x + 0.5;
	all->plr->dir.x = -1;
	all->plr->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0.66;
	if (all->pr->player_dir == 'W')
		rotation(0, all, -M_PI / 2);
	else if (all->pr->player_dir == 'N')
		all->plr->dir.x = -1;
	else if (all->pr->player_dir == 'E')
		rotation(2, all, M_PI / 2);
	else if (all->pr->player_dir == 'S')
		rotation(0, all, M_PI);
	all->win->mlx = mlx_init();
	fill_txtrs(all, parser);
}

static void	fill_imgs(t_all *all)
{
	all->nw.img = all->txtrs.n_wall;
	all->nw.addr = mlx_get_data_addr(all->nw.img,
			&all->nw.bpp, &all->nw.ll, &all->nw.end);
	all->sw.img = all->txtrs.s_wall;
	all->sw.addr = mlx_get_data_addr(all->sw.img,
			&all->sw.bpp, &all->sw.ll, &all->sw.end);
	all->ww.img = all->txtrs.w_wall;
	all->ww.addr = mlx_get_data_addr(all->ww.img,
			&all->ww.bpp, &all->ww.ll, &all->ww.end);
	all->ew.img = all->txtrs.e_wall;
	all->ew.addr = mlx_get_data_addr(all->ew.img,
			&all->ew.bpp, &all->ew.ll, &all->ew.end);
	all->st.img = all->txtrs.sprite;
	all->st.addr = mlx_get_data_addr(all->st.img,
			&all->st.bpp, &all->st.ll, &all->st.end);
}

void		game(t_parser *parser, int is_save)
{
	t_win		win;
	t_player	player;
	t_all		all;
	int			flag;

	flag = 1;
	prepare_struct(&all, &win, &player, parser);
	win.img = mlx_new_image(all.win->mlx, parser->res_x, parser->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.ll, &win.end);
	fill_imgs(&all);
	render_next_frame(&all, is_save, flag);
	flag = 0;
	cub_control(&all);
	mlx_loop(all.win->mlx);
}
