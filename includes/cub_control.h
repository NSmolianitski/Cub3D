/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:58:08 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:58:15 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_CONTROL_H
# define CUB3D_CUB_CONTROL_H

# include "cub_image.h"

int			move(int keycode, t_all *all);
void		cub_control(t_all *all);
void		rotation(int keycode, t_all *all, double rs);
void		move_side(int keycode, t_all *all, double rs, double ms);
int			key_press(int keycode, t_all *all);
int			close_game(t_all *all);

#endif
