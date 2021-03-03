/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_caster.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 20:35:30 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_insert(t_set *s, int y, int re_y)
{
	s->flr.rayDirX0 = s->p.dirX - s->p.planeX;
	s->flr.rayDirY0 = s->p.dirY - s->p.planeY;
	s->flr.rayDirX1 = s->p.dirX + s->p.planeX;
	s->flr.rayDirY1 = s->p.dirY + s->p.planeY;
	s->flr.center = (y - s->minfo.s_height / 2) + (s->updown * 2);
	s->flr.center *= y < re_y ? -1 : 1;
	s->flr.posZ = 0.5 * s->minfo.s_height;
	s->flr.rowDistance = s->flr.posZ / s->flr.center;
	s->flr.floorStepX = s->flr.rowDistance * \
	(s->flr.rayDirX1 - s->flr.rayDirX0) / s->minfo.s_width;
	s->flr.floorStepY = s->flr.rowDistance * \
	(s->flr.rayDirY1 - s->flr.rayDirY0) / s->minfo.s_width;
	s->flr.floorX = s->p.posX + s->flr.rowDistance * s->flr.rayDirX0;
	s->flr.floorY = s->p.posY + s->flr.rowDistance * s->flr.rayDirY0;
}

void	texture_input(t_set *s, int *tex, int texnum)
{
	*tex = texnum;
	s->tex.color = s->p.texture[*tex]\
	[s->img.img_width * s->flr.ty + s->flr.tx];
	s->tex.color = (s->tex.color >> 1) & 8355711;
}

void	fc_kind(t_set *s, int y, int i, int re_y)
{
	if (re_y < 1)
		re_y = 0;
	if (re_y > s->minfo.s_height - 2)
		re_y = s->minfo.s_height - 1;
	if (re_y <= y)
	{
		if (s->minfo.f_kind)
			texture_input(s, &s->tex.floorTexture, 8);
		else
			s->tex.color = s->minfo.floor;
	}
	else
	{
		if (s->minfo.c_kind)
			texture_input(s, &s->tex.ceilingTexture, 10);
		else
			s->tex.color = s->minfo.ceiling;
	}
	s->tex.color = make_darker(s->tex.color, \
	(s->minfo.s_height / 5) - abs(y - re_y));
	s->img.data[(y + s->jump) * s->minfo.s_width + i] = s->tex.color;
}

void	carl_fc(t_set *s)
{
	int x;
	int y;
	int i;
	int	re_y;

	x = 0;
	y = 0;
	i = 0;
	re_y = s->minfo.s_height / 2 - (s->updown * 2);
	while (y < s->minfo.s_height)
	{
		fc_insert(s, y, re_y);
		if (s->updown > s->minfo.s_height / 2)
			s->updown = s->minfo.s_height / 2;
		if (-s->updown > (s->minfo.s_height / 2))
			s->updown = -s->minfo.s_height / 2;
		while (i < s->minfo.s_width)
		{
			s->flr.tx = (int)(s->img.img_width * \
			(s->flr.floorX - (int)(s->flr.floorX))) & (s->img.img_width - 1);
			s->flr.ty = (int)(s->img.img_height * \
			(s->flr.floorY - (int)(s->flr.floorY))) & (s->img.img_height - 1);
			s->flr.floorX += s->flr.floorStepX;
			s->flr.floorY += s->flr.floorStepY;
			fc_kind(s, y, i, re_y);
			i++;
		}
		y++;
		i = 0;
	}
}
