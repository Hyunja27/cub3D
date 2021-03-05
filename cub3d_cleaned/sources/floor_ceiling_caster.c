/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_caster.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:06:57 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_insert(t_set *s, int y, int re_y)
{
	s->flr.raydirx0 = s->p.dirx - s->p.planex;
	s->flr.raydiry0 = s->p.diry - s->p.planey;
	s->flr.raydirx1 = s->p.dirx + s->p.planex;
	s->flr.raydiry1 = s->p.diry + s->p.planey;
	s->flr.center = (y - s->minfo.s_height / 2) + (s->updown * 2);
	s->flr.center *= y < re_y ? -1 : 1;
	s->flr.posz = 0.5 * s->minfo.s_height;
	s->flr.rowdistance = s->flr.posz / s->flr.center;
	s->flr.floorstepx = s->flr.rowdistance * \
	(s->flr.raydirx1 - s->flr.raydirx0) / s->minfo.s_width;
	s->flr.floorstepy = s->flr.rowdistance * \
	(s->flr.raydiry1 - s->flr.raydiry0) / s->minfo.s_width;
	s->flr.floorx = s->p.posx + s->flr.rowdistance * s->flr.raydirx0;
	s->flr.floory = s->p.posy + s->flr.rowdistance * s->flr.raydiry0;
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
	int tmp;

	re_y = (re_y < 1) ? 0 : re_y;
	if (re_y > s->minfo.s_height - 2)
		re_y = s->minfo.s_height - 1;
	if (re_y <= y)
	{
		if (s->minfo.f_kind)
			texture_input(s, &s->tex.floortexture, 8);
		else
			s->tex.color = s->minfo.floor;
	}
	else
	{
		if (s->minfo.c_kind)
			texture_input(s, &s->tex.ceilingtexture, 10);
		else
			s->tex.color = s->minfo.ceiling;
	}
	s->tex.color = make_darker(s->tex.color, \
	(s->minfo.s_height / 5) - abs(y - re_y));
	tmp = (y + s->jump) * s->minfo.s_width + i;
	tmp = (tmp < 0) ? 0 : tmp;
	tmp = (tmp > s->minfo.s_height) ? s->minfo.s_height : tmp;
	s->img.data[(y + s->jump) * s->minfo.s_width + i] = s->tex.color;
}

void	carl_fc(t_set *s)
{
	int y;
	int i;
	int	re_y;

	y = 0;
	i = 0;
	re_y = s->minfo.s_height / 2 - (s->updown * 2);
	while (y < s->minfo.s_height)
	{
		fc_insert(s, y, re_y);
		updown_protect(s);
		while (i < s->minfo.s_width)
		{
			s->flr.tx = (int)(s->img.img_width * \
			(s->flr.floorx - (int)(s->flr.floorx))) & (s->img.img_width - 1);
			s->flr.ty = (int)(s->img.img_height * \
			(s->flr.floory - (int)(s->flr.floory))) & (s->img.img_height - 1);
			s->flr.floorx += s->flr.floorstepx;
			s->flr.floory += s->flr.floorstepy;
			fc_kind(s, y, i, re_y);
			i++;
		}
		y++;
		i = 0;
	}
}
