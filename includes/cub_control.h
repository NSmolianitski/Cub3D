#ifndef CUB3D_CUB_CONTROL_H
#define CUB3D_CUB_CONTROL_H

#include "cub_image.h"

void		move(int keycode, t_all *all);
void		cub_control(t_all *all);
void		rotation(int keycode, t_all *all, double rs);

#endif
