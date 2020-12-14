#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "cub_control.h"
#include "mlx.h"
#include "cub_image.h"
//
//int             move(int keycode, t_all *all)
//{
//	double speed;
//	double oldDirX;
//	double oldPlaneX;
//
//	speed = 0.2;
//	if (keycode == 13 || keycode == 126)
//	{
//		if(all->pr->map[(int)(all->plr->y + all->plr->dir.x * (speed + 0.1))][(int)(all->plr->x)] == '0')
//			all->plr->y += all->plr->dir.x * speed;
//		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir.y * (speed + 0.1))] == '0')
//			all->plr->x += all->plr->dir.y * speed;
//	} else if (keycode == 1 || keycode == 125)
//	{
//		if(all->pr->map[(int)(all->plr->y - all->plr->dir.x * speed)][(int)(all->plr->x)] == '0')
//			all->plr->y -= all->plr->dir.x * speed;
//		if(all->pr->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir.y * speed)] == '0')
//			all->plr->x -= all->plr->dir.y * speed;
//	} else if (keycode == 0 || keycode == 123)
//	{
//		oldDirX = all->plr->dir.x;
//		all->plr->dir.x = all->plr->dir.x * cos(speed) - all->plr->dir.y * sin(speed);
//		all->plr->dir.y = oldDirX * sin(speed) + all->plr->dir.y * cos(speed);
//		oldPlaneX = all->plane.x;
//		all->plane.x = all->plane.x * cos(speed) - all->plane.y * sin(speed);
//		all->plane.y = oldPlaneX * sin(speed) + all->plane.y * cos(speed);
//	} else if (keycode == 2 || keycode == 124)
//	{
//		oldDirX = all->plr->dir.x;
//		all->plr->dir.x = all->plr->dir.x * cos(-speed) - all->plr->dir.y * sin(-speed);
//		all->plr->dir.y = oldDirX * sin(-speed) + all->plr->dir.y * cos(-speed);
//		oldPlaneX = all->plane.x;
//		all->plane.x = all->plane.x * cos(-speed) - all->plane.y * sin(-speed);
//		all->plane.y = oldPlaneX * sin(-speed) + all->plane.y * cos(-speed);
//	}
//	return (1);
//}

//Old movement
int             move(int keycode, t_all *all)
{
	double	speed;

	speed = SCALE / 15;
	if (keycode == 13 || keycode == 126)
	{
		all->plr->x += cos(all->plr->pov) * speed;
		all->plr->y += sin(all->plr->pov) * speed;
	}
	else if (keycode == 1 || keycode == 125)
	{
		all->plr->x -= cos(all->plr->pov) * speed;
		all->plr->y -= sin(all->plr->pov) * speed;
	}
	else if (keycode == 0 || keycode == 123)
	{
		all->plr->pov -= (speed / SCALE * 2);
		if (all->plr->pov <= 0)
			all->plr->pov += 2 * M_PI;
	}
	else if (keycode == 2 || keycode == 124)
	{
		all->plr->pov += (speed / SCALE * 2);
		if (all->plr->pov > 2 * M_PI)
			all->plr->pov -= 2 * M_PI;
	}
	if (all->plr->y < 1)
		all->plr->y = all->pr->res_y - 1;
	else if (all->plr->y >= all->pr->res_y - 1)
		all->plr->y = 0;
	if (all->plr->x < 1)
		all->plr->x = all->pr->res_x - 1;
	else if (all->plr->x >= all->pr->res_x - 1)
		all->plr->x = 0;
	return (1);
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