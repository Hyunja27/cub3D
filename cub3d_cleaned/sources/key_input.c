/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:05:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/02 23:19:44 by spark            ###   ########.fr       */
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
	if (keycode == SPACE_KEY)
		set->space = 1;
	if (keycode == LEFT_ARROW)
		set->left_arrow = 1;
	if (keycode == RIGHT_ARROW)
		set->right_arrow = 1;
	if (keycode == UP_ARROW)
		set->up_arrow = 1;
	if (keycode == DOWN_ARROW)
		set->down_arrow = 1;
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
	if (keycode == LEFT_ARROW)
		set->left_arrow = 0;
	if (keycode == RIGHT_ARROW)
		set->right_arrow = 0;
	if (keycode == UP_KEY)
		set->up = 0;
	if (keycode == DOWN_KEY)
		set->down = 0;
	if (keycode == SPACE_KEY)
	{
		set->space = 0;
		// set->jump = 0;
	}
	if (keycode == LEFT_KEY)
		set->left = 0;
	if (keycode == RIGHT_KEY)
		set->right = 0;
	if (keycode == UP_ARROW)
		set->up_arrow = 0;
	if (keycode == DOWN_ARROW)
		set->down_arrow = 0;
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
	if (s->left_arrow == 1)
	{
		s->olddir_x = s->p.dirX;
		s->p.dirX = s->p.dirX * cos(s->p.rspd) - s->p.dirY * sin(s->p.rspd);
		s->p.dirY = s->olddir_x * sin(s->p.rspd) + s->p.dirY * cos(s->p.rspd);
		s->oldplane_x = s->p.planeX;
		s->p.planeX = s->p.planeX * cos(s->p.rspd) - \
		s->p.planeY * sin(s->p.rspd);
		s->p.planeY = s->oldplane_x * sin(s->p.rspd) + \
		s->p.planeY * cos(s->p.rspd);
	}
	if (s->right_arrow == 1)
	{
		s->olddir_x = s->p.dirX;
		s->p.dirX = s->p.dirX * cos(-s->p.rspd) - s->p.dirY * sin(-s->p.rspd);
		s->p.dirY = s->olddir_x * sin(-s->p.rspd) + s->p.dirY * cos(-s->p.rspd);
		s->oldplane_x = s->p.planeX;
		s->p.planeX = s->p.planeX * cos(-s->p.rspd) - \
		s->p.planeY * sin(-s->p.rspd);
		s->p.planeY = s->oldplane_x * sin(-s->p.rspd) + \
		s->p.planeY * cos(-s->p.rspd);
	}
	if (s->up_arrow == 1)
	{
		s->updown -= 4;
	}
	if (s->down_arrow == 1)
	{
		s->updown += 4;
	}
	if (s->space == 1)
	{
		s->jump = 1;
	}
	
}

void		key_action(t_set *s)
{
	if (s->right == 1)
	{
		s->olddir_x = s->p.dirX * cos(M_PI_2) - s->p.dirY * sin(M_PI_2);
		s->olddir_y = s->p.dirX * sin(M_PI_2) + s->p.dirY * cos(M_PI_2);
		if (!s->map2[(int)(s->p.posX - s->olddir_x * s->p.movespeed)][(int)s->p.posY])
			s->p.posX -= s->olddir_x * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX += s->olddir_x / 2;
		}
		if (!s->map2[(int)s->p.posX][(int)(s->p.posY - s->olddir_y * s->p.movespeed)])
			s->p.posY -= s->olddir_y * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX += s->olddir_x / 2;
		}
	}
	if (s->left == 1)
	{
		s->olddir_x = s->p.dirX * cos(M_PI_2) - s->p.dirY * sin(M_PI_2);
		s->olddir_y = s->p.dirX * sin(M_PI_2) + s->p.dirY * cos(M_PI_2);
		if (!s->map2[(int)(s->p.posX + s->olddir_x * s->p.movespeed)][(int)s->p.posY])
			s->p.posX += s->olddir_x * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX -= s->olddir_x / 2;
		}
		if (!s->map2[(int)s->p.posX][(int)(s->p.posY + s->olddir_y * s->p.movespeed)])
			s->p.posY += s->olddir_y * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posY -= s->olddir_y / 2;
		}
	}
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
		s->life -= 5.5;
		s->collision = 0;
		sound_effect(3);
	}
	key_action_2(s);
}
