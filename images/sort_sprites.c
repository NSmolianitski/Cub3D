/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:56:50 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:57:35 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_image.h"

static void	sort(t_sprites sprites[], int sprites_num)
{
	t_sprites	tmp;
	int			i;
	int			j;
	int			f;

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

static void	reverse_sprites(int s_num, t_sprites s[], double *dist, int order[])
{
	int i;

	i = 0;
	while (i < s_num)
	{
		dist[i] = s[s_num - i - 1].dist;
		order[i] = s[s_num - i - 1].order;
		++i;
	}
}

void		sort_sprites(double *dist, int order[], int sprites_num, t_all *all)
{
	int			i;
	t_sprites	sprites[sprites_num];

	i = 0;
	while (i < all->pr->objs_num)
	{
		order[i] = i;
		dist[i] = (all->plr->x - all->pr->objs[i].x) * (all->plr->x -
				all->pr->objs[i].x) + (all->plr->y - all->pr->objs[i].y)
			* (all->plr->y - all->pr->objs[i].y);
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
	reverse_sprites(sprites_num, sprites, dist, order);
}
