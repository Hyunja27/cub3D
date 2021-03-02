/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:59:26 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 00:13:20 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_cast_end(t_set *s, int x, int y, int i)
{
	int w;
	int	tmp;

	while (x < s->spr.drawEndX)
	{
		s->spr.texX = (int)((256 * (x - (-s->spr.sp_sc_W / 2 + \
		s->spr.spriteScreenX)) * TEX_WIDTH / s->spr.sp_sc_W) / 256);
		w = s->minfo.s_width;
		if (s->spr.tr_Y > 0 && x > 0 && x < w && s->spr.tr_Y < \
		s->p.zBuffer[x])
		{
			y = s->spr.drawStartY;
			while (y < s->spr.drawEndY)
			{
				s->spr.d = (y - s->spr.vMoveScreen) * 256 - \
				s->minfo.s_height * 128 + s->spr.sp_sc_H * 128;
				s->spr.texY = ((s->spr.d * TEX_HEIGHT) / s->spr.sp_sc_H) / 256;
				s->spr.spr_color = s->p.texture[s->spr.sprt[s->spr.spriteOrder[i]].texnum][s->spr.texY * \
				TEX_WIDTH + s->spr.texX];
				tmp = (y - (s->updown * 2) + s->jump) * s->minfo.s_width + (x + s->time);
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
	s->spr.sp_X = s->spr.sprt[s->spr.spriteOrder[i]].x - s->p.posX;
	s->spr.sp_Y = s->spr.sprt[s->spr.spriteOrder[i]].y - s->p.posY;
	s->spr.invDet = 1.0 / (s->p.planeX * s->p.dirY - s->p.dirX * s->p.planeY);
	s->spr.tr_X = s->spr.invDet * \
	(s->p.dirY * s->spr.sp_X - s->p.dirX * s->spr.sp_Y);
	s->spr.tr_Y = s->spr.invDet * \
	(-s->p.planeY * s->spr.sp_X + s->p.planeX * s->spr.sp_Y);
	s->spr.spriteScreenX = (int)\
	((s->minfo.s_width / 2) * (1 + s->spr.tr_X / s->spr.tr_Y));
	s->spr.uDiv = 1;
	s->spr.vDiv = 1;
	s->spr.vMove = 0.0;
	s->spr.vMoveScreen = (int)(s->spr.vMove / s->spr.tr_Y);
	s->spr.sp_sc_H = (int)fabs((s->minfo.s_height / s->spr.tr_Y) / s->spr.vDiv);
	s->spr.drawStartY = (s->minfo.s_height / 2 + \
	s->spr.vMoveScreen) - s->spr.sp_sc_H / 2;
	s->spr.drawEndY = (s->minfo.s_height / 2 + \
	s->spr.vMoveScreen) + s->spr.sp_sc_H / 2;
	s->spr.drawStartY = s->spr.drawStartY < 0 ? 0 : s->spr.drawStartY;
}

void	sprite_cast_insert_2(t_set *s, int i)
{
	int a;

	a = i;
	s->spr.drawEndY = s->spr.drawEndY >= s->minfo.s_height ? \
	s->minfo.s_height - 1 : s->spr.drawEndY;
	s->spr.sp_sc_W = (int)fabs((s->minfo.s_height / s->spr.tr_Y) / s->spr.uDiv);
	s->spr.drawStartX = s->spr.spriteScreenX - s->spr.sp_sc_W / 2;
	s->spr.drawEndX = s->spr.spriteScreenX + s->spr.sp_sc_W / 2;
	s->spr.drawStartX = s->spr.drawStartX < 0 ? 0 : s->spr.drawStartX;
	s->spr.drawEndX = s->spr.drawEndX >= s->minfo.s_width ? \
	s->minfo.s_width - 1 : s->spr.drawEndX;
}

void	sprite_cast(t_set *s)
{
	int i;
	int x;
	int y;

	i = -1;
	x = 0;
	y = 0;
	s->spr.spriteOrder = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
	s->spr.spriteDistance = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
	while (++i < s->minfo.num_sprite)
	{
		s->spr.spriteOrder[i] = i;
		s->spr.spriteDistance[i] = ((s->p.posX - s->spr.sprt[i].x) * \
		(s->p.posX - s->spr.sprt[i].x) + \
		(s->p.posY - s->spr.sprt[i].y) * (s->p.posY - s->spr.sprt[i].y));
	}
	i = -1;
	arrange_sprite(s);
	while (++i < s->minfo.num_sprite)
	{
		sprite_cast_insert_1(s, i);
		sprite_cast_insert_2(s, i);
		x = s->spr.drawStartX;
		sprite_cast_end(s, x, y, i);
	}
}
