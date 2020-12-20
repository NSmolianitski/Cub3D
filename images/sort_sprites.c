#include "cub_image.h"

static void	sort(t_sprites sprites[], int sprites_num)
{
	t_sprites	tmp;
	int 		i;
	int 		j;
	int 		f;

	j = 1;
	while (j < sprites_num)
	{
		i = 0;
		f = 0;
		while (i < sprites_num - j)
		{
			if (sprites[i].dist > sprites[i + 1].dist)
			{
				tmp = sprites[i + 1];
				sprites[i + 1] = sprites[i];
				sprites[i] = tmp;
				f = 1;
			}
			++i;
		}
		if (!f)
			break ;
		++j;
	}
}

void		sort_sprites(double *dist, int order[], int sprites_num, t_all *all)
{
	int	i;
	t_sprites sprites[sprites_num];

	i = 0;
	while (i < all->pr->objs_num)
	{
		order[i] = i;
		dist[i] = (all->plr->x - all->pr->objs[i].x) * (all->plr->x - all->pr->objs[i].x) + (all->plr->y - all->pr->objs[i].y) * (all->plr->y - all->pr->objs[i].y); //sqrt not taken, unneeded
		++i;
	}
	i = 0;
	while (i < sprites_num)
	{
		sprites[i].dist = dist[i];
		sprites[i].order = order[i];
		++i;
	}
	sort(sprites, sprites_num);
	i = 0;
	while (i < sprites_num)
	{
		dist[i] = sprites[sprites_num - i - 1].dist;
		order[i] = sprites[sprites_num - i - 1].order;
		++i;
	}
}
