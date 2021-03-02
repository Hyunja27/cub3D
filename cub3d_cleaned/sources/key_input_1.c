/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:05:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 00:26:47 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_action_5(t_set *s)
{
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
	if (s->collision)
	{
		s->life -= 5.5;
		s->collision = 0;
		sound_effect(3);
	}
}

void	key_action_4(t_set *s)
{
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
	key_action_5(s);
}

void		key_action_3(t_set *s)
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
	if (s->up_arrow == 1)
		s->updown -= 4;
	if (s->down_arrow == 1)
		s->updown += 4;
	if (s->space == 1)
		s->jump = 1;
	key_action_4(s);
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
	key_action_3(s);
}

void		key_action(t_set *s)
{
	if (s->right == 1)
	{
		s->olddir_x = s->p.dirX * cos(M_PI_2) - s->p.dirY * sin(M_PI_2);
		s->olddir_y = s->p.dirX * sin(M_PI_2) + s->p.dirY * cos(M_PI_2);
		if (!s->map2[(int)(s->p.posX - s->olddir_x * \
		s->p.movespeed)][(int)s->p.posY])
			s->p.posX -= s->olddir_x * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX += s->olddir_x / 2;
		}
		if (!s->map2[(int)s->p.posX][(int)(s->p.posY - \
		s->olddir_y * s->p.movespeed)])
			s->p.posY -= s->olddir_y * s->p.movespeed;
		else
		{
			s->collision = 1;
			s->p.posX += s->olddir_x / 2;
		}
	}
	key_action_2(s);
}
