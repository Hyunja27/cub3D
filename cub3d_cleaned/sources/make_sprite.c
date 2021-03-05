/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:59:26 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 17:15:17 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_cast_end_2(t_set *s, int y, int i)
{
	s->spr.d = (y - s->spr.vmovescreen) * 256 - \
	s->minfo.s_height * 128 + s->spr.sp_sc_h * 128;
	s->spr.texy = ((s->spr.d * TEX_HEIGHT) / s->spr.sp_sc_h) / 256;
	s->spr.spr_color = s->p.texture\
	[s->spr.sprt[s->spr.spriteorder[i]].texnum]\
	[s->spr.texy * TEX_WIDTH + s->spr.texx];
	s->spr.spr_color = make_darker(s->spr.spr_color, \
	s->spr.spritedistance[i] * 3);
}

void	sprite_cast_end(t_set *s, int x, int y, int i)
{
	int w;
	int	tmp;

	while (x < s->spr.drawendx)
	{
		s->spr.texx = (int)((256 * (x - (-s->spr.sp_sc_w / 2 + \
		s->spr.spritescreenx)) * TEX_WIDTH / s->spr.sp_sc_w) / 256);
		w = s->minfo.s_width;
		if (s->spr.tr_y > 0 && x > 0 && x < w && s->spr.tr_y < \
		s->p.zBuffer[x])
		{
			y = s->spr.drawstarty;
			while (y < s->spr.drawendy)
			{
				sprite_cast_end_2(s, y, i);
				tmp = ((y + s->time) - (s->updown * 2) + s->jump) \
				* s->minfo.s_width + (x);
				tmp = tmp < 0 ? 0 : tmp;
				if ((s->spr.spr_color & 0x00FFFFFF) != 0)
					s->img.data[tmp] = s->spr.spr_color;
				y++;
			}
		}
		x++;
	}
}

void	sprite_cast_insert_1(t_set *s, int i)
{
	s->spr.sp_x = s->spr.sprt[s->spr.spriteorder[i]].x - s->p.posx;
	s->spr.sp_y = s->spr.sprt[s->spr.spriteorder[i]].y - s->p.posy;
	s->spr.invdet = 1.0 / (s->p.planex * s->p.diry - s->p.dirx * s->p.planey);
	s->spr.tr_x = s->spr.invdet * \
	(s->p.diry * s->spr.sp_x - s->p.dirx * s->spr.sp_y);
	s->spr.tr_y = s->spr.invdet * \
	(-s->p.planey * s->spr.sp_x + s->p.planex * s->spr.sp_y);
	s->spr.spritescreenx = (int)\
	((s->minfo.s_width / 2) * (1 + s->spr.tr_x / s->spr.tr_y));
	s->spr.udiv = 1;
	s->spr.vdiv = 1;
	s->spr.vmove = 0.0;
	s->spr.vmovescreen = (int)(s->spr.vmove / s->spr.tr_y);
	s->spr.sp_sc_h = (int)fabs((s->minfo.s_height / s->spr.tr_y) / s->spr.vdiv);
	s->spr.drawstarty = (s->minfo.s_height / 2 + \
	s->spr.vmovescreen) - s->spr.sp_sc_h / 2;
	s->spr.drawendy = (s->minfo.s_height / 2 + \
	s->spr.vmovescreen) + s->spr.sp_sc_h / 2;
	s->spr.drawstarty = s->spr.drawstarty < 0 ? 0 : s->spr.drawstarty;
}

void	sprite_cast_insert_2(t_set *s, int i)
{
	int a;

	a = i;
	s->spr.drawendy = s->spr.drawendy >= s->minfo.s_height ? \
	s->minfo.s_height - 1 : s->spr.drawendy;
	s->spr.sp_sc_w = (int)fabs((s->minfo.s_height / s->spr.tr_y) / s->spr.udiv);
	s->spr.drawstartx = s->spr.spritescreenx - s->spr.sp_sc_w / 2;
	s->spr.drawendx = s->spr.spritescreenx + s->spr.sp_sc_w / 2;
	s->spr.drawstartx = s->spr.drawstartx < 0 ? 0 : s->spr.drawstartx;
	s->spr.drawendx = s->spr.drawendx >= s->minfo.s_width ? \
	s->minfo.s_width - 1 : s->spr.drawendx;
}

void	sprite_cast(t_set *s)
{
	int i;
	int y;

	i = -1;
	y = 0;
	s->spr.spriteorder = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
	s->spr.spritedistance = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
	while (++i < s->minfo.num_sprite)
	{
		s->spr.spriteorder[i] = i;
		s->spr.spritedistance[i] = ((s->p.posx - s->spr.sprt[i].x) * \
		(s->p.posx - s->spr.sprt[i].x) + \
		(s->p.posy - s->spr.sprt[i].y) * (s->p.posy - s->spr.sprt[i].y));
	}
	i = -1;
	arrange_sprite(s);
	while (++i < s->minfo.num_sprite)
	{
		sprite_cast_insert_1(s, i);
		sprite_cast_insert_2(s, i);
		sprite_cast_end(s, s->spr.drawstartx, y, i);
	}
	free(s->spr.spritedistance);
	free(s->spr.spriteorder);
}
