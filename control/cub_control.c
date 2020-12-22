#include "cub_control.h"
#include "mlx.h"
#include "cub_image.h"

static void move_rotation(int keycode, t_all *all, double rs, double ms)
{
	if (keycode == 123)
		rotation(123, all, rs);
	else if (keycode == 124)
		rotation(124, all, rs);
	else if (keycode == 0)
		move_side(0, all, rs, ms);
	else if (keycode == 2)
		move_side(2, all, rs, ms);
}

static void move_forward(t_all *all, double ms)
{
	if (all->pr->map[(int)(all->plr->y + all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
		all->plr->y += all->plr->dir.x * ms;
	if (all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * ms)] != '1')
		all->plr->x += all->plr->dir.y * ms;
}

int			move(int keycode, t_all *all)
{
	double	ms;
	double	rs;

	ms = 0.1;
	rs = 0.1;
	if (keycode == 13 || keycode == 126)
		move_forward(all, ms);
	else if (keycode == 1 || keycode == 125)
	{
		if (all->pr->map[(int)(all->plr->y - all->plr->dir.x * ms)][(int)(all->plr->x)] != '1')
			all->plr->y -= all->plr->dir.x * ms;
		if (all->pr->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir.y * ms)] != '1')
			all->plr->x -= all->plr->dir.y * ms;
	}
	else
		move_rotation(keycode, all, rs, ms);
	render_next_frame(all, 0, 0);
	return (0);
}

void		cub_control(t_all *all)
{
	mlx_hook(all->win->win, 17, 0L, close_game, all);
	mlx_key_hook(all->win->win, key_press, all);
	mlx_hook(all->win->win, 2, 1L >> 0, move, all);
}