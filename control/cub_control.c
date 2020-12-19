#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "cub_control.h"
#include "mlx.h"
#include "cub_image.h"

void	rotation(int keycode, t_all *all, double rs)
{
	double	old_x;
	double	old_plane_x;

	if (keycode == 123)
	{
		old_x = all->plr->dir.x;
		all->plr->dir.x = all->plr->dir.x * cos(rs) - all->plr->dir.y * sin(rs);
		all->plr->dir.y = old_x * sin(rs) + all->plr->dir.y * cos(rs);
		old_plane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(rs) - all->plane.y * sin(rs);
		all->plane.y = old_plane_x * sin(rs) + all->plane.y * cos(rs);
	}
	else
	{
		old_x = all->plr->dir.x;
		all->plr->dir.x = all->plr->dir.x * cos(-rs) - all->plr->dir.y * sin(-rs);
		all->plr->dir.y = old_x * sin(-rs) + all->plr->dir.y * cos(-rs);
		old_plane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(-rs) - all->plane.y * sin(-rs);
		all->plane.y = old_plane_x * sin(-rs) + all->plane.y * cos(-rs);
	}
}

void	move_side(int keycode, t_all *all, double rs, double ms)
{
	if (keycode == 2)
	{
		for (int x = 0; x < 15.00000000001; ++x)
			rotation(124, all, rs);
		if(all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y += all->plr->dir.x * ms;
		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
			all->plr->x += all->plr->dir.y * ms;
		for (int x = 0; x < 15.00000000001; ++x)
			rotation(123, all, rs);
	}
	else
	{
		for (int x = 0; x < 15.00000000001; ++x)
			rotation(123, all, rs);
		if(all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y += all->plr->dir.x * ms;
		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
			all->plr->x += all->plr->dir.y * ms;
		for (int x = 0; x < 15.00000000001; ++x)
			rotation(124, all, rs);
	}
}

void	move(int keycode, t_all *all)
{
	double	ms = 0.1;
	double	rs = 0.1;

	if (keycode == 13 || keycode == 126)
	{
		if(all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y += all->plr->dir.x * ms;
		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
			all->plr->x += all->plr->dir.y * ms;
	}
	else if (keycode == 1 || keycode == 125)
	{
		if(all->pr->map[(int)(all->plr->y - all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y -= all->plr->dir.x * ms;
		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir.y * ms)] != '1')
			all->plr->x -= all->plr->dir.y * ms;
	}
	else if (keycode == 123)
		rotation(123, all, rs);
	else if (keycode == 124)
		rotation(124, all, rs);
	else if (keycode == 0)
		move_side(0, all, rs, ms);
	else if (keycode == 2)
		move_side(2, all, rs, ms);
	render_next_frame(all);
}

static int	close_game(t_all *all)
{
	mlx_destroy_window(all->win->mlx, all->win->win);
	write(1, "Game is closed, bye!", 20);
	exit(0);
}

int key_press(int keycode, t_all *all)
{
	if (keycode == 53)
		close_game(all);
	return (1);
}

void		cub_control(t_all *all)
{
	//Game closing (red cross or ESC)
	mlx_hook(all->win->win, 17, 0L, close_game, all);
	mlx_key_hook(all->win->win, key_press, all);
	//Movement
	mlx_hook(all->win->win, 2, 1L>>0, move, all);
}