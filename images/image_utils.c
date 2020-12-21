#include "cub_image.h"

void			fast_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char    *dst;

	dst = win->addr + (y * win->ll + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

int				rgb_to_hex(int arr[3])
{
	return ((arr[0] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[2] & 0xff);
}

int				get_tex_color(t_win *texture, int x, int y)
{
	int color;

	color = *(unsigned int*)(texture->addr + (y * texture->ll + x * (texture->bpp / 8)));
	return (color);
}