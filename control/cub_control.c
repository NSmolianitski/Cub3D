#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "cub_control.h"
#include "mlx.h"
#include "cub_image.h"

double moveSpeed = 0.1; //the constant value is in squares/second
double rotSpeed = 0.1; //the constant value is in radians/second

//lodev movement
int 	move(int keycode, t_all *all)
{
	double	old_x;
	double	old_plane_x;
	if (keycode == 13 || keycode == 126)
	{
		if(all->pr->map[(int)(all->plr->x + all->plr->dir.x * moveSpeed)][(int)(all->plr->y)] == '0') all->plr->x += all->plr->dir.x * moveSpeed;
		if(all->pr->map[(int)(all->plr->x)][(int)(all->plr->y + all->plr->dir.y * moveSpeed)] == '0') all->plr->y += all->plr->dir.y * moveSpeed;
	} else if (keycode == 1 || keycode == 125)
	{
		if(all->pr->map[(int)(all->plr->x - all->plr->dir.x * moveSpeed)][(int)(all->plr->y)] == '0') all->plr->x -= all->plr->dir.x * moveSpeed;
		if(all->pr->map[(int)(all->plr->x)][(int)(all->plr->y - all->plr->dir.y * moveSpeed)] == '0') all->plr->y -= all->plr->dir.y * moveSpeed;
	} else if (keycode == 0 || keycode == 123)
	{
		//both camera direction and camera plane must be rotated
		old_x = all->plr->dir.x;
		all->plr->dir.x = all->plr->dir.x * cos(rotSpeed) - all->plr->dir.y * sin(rotSpeed);
		all->plr->dir.y = old_x * sin(rotSpeed) + all->plr->dir.y * cos(rotSpeed);
		old_plane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(rotSpeed) - all->plane.y * sin(rotSpeed);
		all->plane.y = old_plane_x * sin(rotSpeed) + all->plane.y * cos(rotSpeed);
	} else if (keycode == 2 || keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		old_x = all->plr->dir.x;
		all->plr->dir.x = all->plr->dir.x * cos(-rotSpeed) - all->plr->dir.y * sin(-rotSpeed);
		all->plr->dir.y = old_x * sin(-rotSpeed) + all->plr->dir.y * cos(-rotSpeed);
		old_plane_x = all->plane.x;
		all->plane.x = all->plane.x * cos(-rotSpeed) - all->plane.y * sin(-rotSpeed);
		all->plane.y = old_plane_x * sin(-rotSpeed) + all->plane.y * cos(-rotSpeed);
	}
	render_next_frame(all);
	return (1);
}

////Old movement
//int             move(int keycode, t_all *all)
//{
//	double	speed;
//
//	speed = 4;
//	if (keycode == 13 || keycode == 126)
//	{
//		all->plr->x += cos(all->plr->pov) * speed;
//		all->plr->y += sin(all->plr->pov) * speed;
//	}
//	else if (keycode == 1 || keycode == 125)
//	{
//		all->plr->x -= cos(all->plr->pov) * speed;
//		all->plr->y -= sin(all->plr->pov) * speed;
//	}
//	else if (keycode == 0 || keycode == 123)
//	{
//		all->plr->pov -= (speed / SCALE * 2);
//		if (all->plr->pov <= 0)
//			all->plr->pov += 2 * M_PI;
//	}
//	else if (keycode == 2 || keycode == 124)
//	{
//		all->plr->pov += (speed / SCALE * 2);
//		if (all->plr->pov > 2 * M_PI)
//			all->plr->pov -= 2 * M_PI;
//	}
//	if (all->plr->y < 1)
//		all->plr->y = all->pr->res_y - 1;
//	else if (all->plr->y >= all->pr->res_y - 1)
//		all->plr->y = 0;
//	if (all->plr->x < 1)
//		all->plr->x = all->pr->res_x - 1;
//	else if (all->plr->x >= all->pr->res_x - 1)
//		all->plr->x = 0;
//	render_next_frame(all);
//	return (1);
//}

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