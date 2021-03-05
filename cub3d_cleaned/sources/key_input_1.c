/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:05:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:11:55 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_action_5(t_set *s)
{
	if (s->left == 1)
	{
		s->olddir_x = s->p.dirx * cos(M_PI_2) - s->p.diry * sin(M_PI_2);
		s->olddir_y = s->p.dirx * sin(M_PI_2) + s->p.diry * cos(M_PI_2);
		if (!s->map2[(int)(s->p.posx + s->olddir_x * s->p.movespeed)]\
		[(int)s->p.posy])
			s->p.posx += s->olddir_x * s->p.movespeed;
		else
			collision_damage(s, &s->p.posx, -s->olddir_x / 2);
		if (!s->map2[(int)s->p.posx]\
		[(int)(s->p.posy + s->olddir_y * s->p.movespeed)])
			s->p.posy += s->olddir_y * s->p.movespeed;
		else
			collision_damage(s, &s->p.posy, -s->olddir_y / 2);
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
		if (!s->map2[(int)(s->p.posx - s->p.dirx * s->p.movespeed)]\
		[(int)s->p.posy])
			s->p.posx -= s->p.dirx * s->p.movespeed;
		else
			collision_damage(s, &s->p.posx, +s->p.dirx / 2);
		if (!s->map2[(int)s->p.posx]\
		[(int)(s->p.posy - s->p.diry * s->p.movespeed)])
			s->p.posy -= s->p.diry * s->p.movespeed;
		else
			collision_damage(s, &s->p.posy, s->p.diry / 2);
	}
	key_action_5(s);
}

void	key_action_3(t_set *s)
{
	if (s->up == 1)
	{
		if (!s->map2[(int)(s->p.posx + s->p.dirx * s->p.movespeed)]\
		[(int)s->p.posy])
			s->p.posx += s->p.dirx * s->p.movespeed;
		else
			collision_damage(s, &s->p.posx, -s->p.dirx / 2);
		if (!s->map2[(int)s->p.posx]\
		[(int)(s->p.posy + s->p.diry * s->p.movespeed)])
			s->p.posy += s->p.diry * s->p.movespeed;
		else
			collision_damage(s, &s->p.posy, -s->p.diry / 2);
	}
	if (s->up_arrow == 1)
		s->updown -= 4;
	if (s->down_arrow == 1)
		s->updown += 4;
	if (s->space == 1)
		s->jump = 1;
	key_action_4(s);
}

void	key_action_2(t_set *s)
{
	if (s->left_arrow == 1)
	{
		s->olddir_x = s->p.dirx;
		s->p.dirx = s->p.dirx * cos(s->p.rspd) - s->p.diry * sin(s->p.rspd);
		s->p.diry = s->olddir_x * sin(s->p.rspd) + s->p.diry * cos(s->p.rspd);
		s->oldplane_x = s->p.planex;
		s->p.planex = s->p.planex * cos(s->p.rspd) - \
		s->p.planey * sin(s->p.rspd);
		s->p.planey = s->oldplane_x * sin(s->p.rspd) + \
		s->p.planey * cos(s->p.rspd);
	}
	if (s->right_arrow == 1)
	{
		s->olddir_x = s->p.dirx;
		s->p.dirx = s->p.dirx * cos(-s->p.rspd) - s->p.diry * sin(-s->p.rspd);
		s->p.diry = s->olddir_x * sin(-s->p.rspd) + s->p.diry * cos(-s->p.rspd);
		s->oldplane_x = s->p.planex;
		s->p.planex = s->p.planex * cos(-s->p.rspd) - \
		s->p.planey * sin(-s->p.rspd);
		s->p.planey = s->oldplane_x * sin(-s->p.rspd) + \
		s->p.planey * cos(-s->p.rspd);
	}
	key_action_3(s);
}

void	key_action(t_set *s)
{
	if (s->right == 1)
	{
		s->olddir_x = s->p.dirx * cos(M_PI_2) - s->p.diry * sin(M_PI_2);
		s->olddir_y = s->p.dirx * sin(M_PI_2) + s->p.diry * cos(M_PI_2);
		if (!s->map2[(int)(s->p.posx - s->olddir_x * \
		s->p.movespeed)][(int)s->p.posy])
			s->p.posx -= s->olddir_x * s->p.movespeed;
		else
			collision_damage(s, &s->p.posx, s->olddir_x / 2);
		if (!s->map2[(int)s->p.posx][(int)(s->p.posy - \
		s->olddir_y * s->p.movespeed)])
			s->p.posy -= s->olddir_y * s->p.movespeed;
		else
			collision_damage(s, &s->p.posx, s->olddir_x / 2);
	}
	key_action_2(s);
}
