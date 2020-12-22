#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"
#include "cub_image.h"

void		rotation(int keycode, t_all *all, double rs)
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

static void	move_left(t_all *all, double ms, double rs)
{
	int	x;

	x = 0;
	while (x < 15.00000000001)
	{
		rotation(123, all, rs);
		++x;
	}
	if (all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
		all->plr->y += all->plr->dir.x * ms;
	if (all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
		all->plr->x += all->plr->dir.y * ms;
	x = 0;
	while (x < 15.00000000001)
	{
		rotation(124, all, rs);
		++x;
	}
}

void		move_side(int keycode, t_all *all, double rs, double ms)
{
	int	x;

	if (keycode == 2)
	{
		x = 0;
		while (x < 15.00000000001)
		{
			rotation(124, all, rs);
			++x;
		}
		if (all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y += all->plr->dir.x * ms;
		if (all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
			all->plr->x += all->plr->dir.y * ms;
		x = 0;
		while (x < 15.00000000001)
		{
			rotation(123, all, rs);
			++x;
		}
	}
	else
		move_left(all, ms, rs);
}

int			close_game(t_all *all)
{
	mlx_destroy_window(all->win->mlx, all->win->win);
	write(1, "Game is closed, bye!", 20);
	exit(0);
}

int			key_press(int keycode, t_all *all)
{
	if (keycode == 53)
		close_game(all);
	return (1);
}