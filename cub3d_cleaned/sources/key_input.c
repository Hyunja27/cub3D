/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:05:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 18:27:45 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press(int keycode, t_set *set)
{
	if (keycode == ESC_KEY)
	{
		system("killall afplay");
		sound_effect(2);
		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		exit(0);
	}
	if (keycode == LEFT_KEY)
		set->left = 1;
	if (keycode == RIGHT_KEY)
		set->right = 1;
	if (keycode == UP_KEY)
		set->up = 1;
	if (keycode == DOWN_KEY)
		set->down = 1;
	if (keycode == P_KEY)
	{
		make_bmp(set);
		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		exit(0);
	}
	return (0);
}

int			key_release(int keycode, t_set *set)
{
	if (keycode == LEFT_KEY)
		set->left = 0;
	if (keycode == RIGHT_KEY)
		set->right = 0;
	if (keycode == UP_KEY)
		set->up = 0;
	if (keycode == DOWN_KEY)
		set->down = 0;
	if (keycode == M_KEY)
	{
		if (set->map1 == 0)
			set->map1 = 1;
		else
			set->map1 = 0;
	}
	return (0);
}

void		key_action_2(t_set *s)
{
	double olddir_x;
	double oldplane_x;

	if (s->left == 1)
	{
		olddir_x = s->p.dirX;
		s->p.dirX = s->p.dirX * cos(s->p.rspd) - s->p.dirY * sin(s->p.rspd);
		s->p.dirY = olddir_x * sin(s->p.rspd) + s->p.dirY * cos(s->p.rspd);
		oldplane_x = s->p.planeX;
		s->p.planeX = s->p.planeX * cos(s->p.rspd) - \
		s->p.planeY * sin(s->p.rspd);
		s->p.planeY = oldplane_x * sin(s->p.rspd) + \
		s->p.planeY * cos(s->p.rspd);
	}
	if (s->right == 1)
	{
		olddir_x = s->p.dirX;
		s->p.dirX = s->p.dirX * cos(-s->p.rspd) - s->p.dirY * sin(-s->p.rspd);
		s->p.dirY = olddir_x * sin(-s->p.rspd) + s->p.dirY * cos(-s->p.rspd);
		oldplane_x = s->p.planeX;
		s->p.planeX = s->p.planeX * cos(-s->p.rspd) - \
		s->p.planeY * sin(-s->p.rspd);
		s->p.planeY = oldplane_x * sin(-s->p.rspd) + \
		s->p.planeY * cos(-s->p.rspd);
	}
}

void		key_action(t_set *s)
{
	if (s->up == 1)
	{
		if (!s->map2[(int)(s->p.posX + s->p.dirX * s->p.movespeed)]\
		[(int)s->p.posY])
			s->p.posX += s->p.dirX * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX -= s->p.dirX / 2;
		}
		if (!s->map2[(int)s->p.posX]\
		[(int)(s->p.posY + s->p.dirY * s->p.movespeed)])
			s->p.posY += s->p.dirY * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posY -= s->p.dirY / 2;
		}
			
	}
	if (s->down == 1)
	{
		if (!s->map2[(int)(s->p.posX - s->p.dirX * s->p.movespeed)]\
		[(int)s->p.posY])
			s->p.posX -= s->p.dirX * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX -= s->p.dirX / 2;
		}
		if (!s->map2[(int)s->p.posX]\
		[(int)(s->p.posY - s->p.dirY * s->p.movespeed)])
			s->p.posY -= s->p.dirY * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posY += s->p.dirY / 2;
		}
	}
	if (s->collision)
	{
		s->life -= 0.5;
		s->collision = 0;
		sound_effect(3);
	}
	key_action_2(s);
}
