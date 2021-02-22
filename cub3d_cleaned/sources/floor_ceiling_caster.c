/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_caster.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/02/23 01:05:37 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fc_insert(t_set *s, int y)
{
	s->flr.rayDirX0 = s->p.dirX - s->p.planeX;
	s->flr.rayDirY0 = s->p.dirY - s->p.planeY;
	s->flr.rayDirX1 = s->p.dirX + s->p.planeX;
	s->flr.rayDirY1 = s->p.dirY + s->p.planeY;
	s->flr.center = y - s->minfo.s_height / 2;
	s->flr.posZ = 0.5 * s->minfo.s_height;
	s->flr.rowDistance = s->flr.posZ / s->flr.center;
	s->flr.floorStepX = s->flr.rowDistance * (s->flr.rayDirX1 - s->flr.rayDirX0) / s->minfo.s_width;
	s->flr.floorStepY = s->flr.rowDistance * (s->flr.rayDirY1 - s->flr.rayDirY0) / s->minfo.s_width;
	s->flr.floorX = s->p.posX + s->flr.rowDistance * s->flr.rayDirX0;
	s->flr.floorY = s->p.posY + s->flr.rowDistance * s->flr.rayDirY0;
}

void fc_kind(t_set *s, int y, int i)
{
	if (s->minfo.f_kind)
	{   
		s->tex.floorTexture = 8;
		s->tex.color = s->p.texture[s->tex.floorTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
		s->tex.color = (s->tex.color >> 1) & 8355711;
	}
	else
		s->tex.color = s->minfo.floor;
	s->img.data[y * s->minfo.s_width + i] = s->tex.color;
	if (s->minfo.c_kind)
	{
		s->tex.ceilingTexture = 10;
		s->tex.color = s->p.texture[s->tex.ceilingTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
		s->tex.color = (s->tex.color >> 1) & 8355711;
	}
	else
		s->tex.color = s->minfo.ceiling;
	s->img.data[(s->minfo.s_height - y - 1) * s->minfo.s_width + i] = s->tex.color;
}

void carl_fc(t_set *s)
{
	int x;
	int y;
	int i;
	             
	x = 0;
	y = 0;
	i = 0;
	
	while (y < s->minfo.s_height)
	{
		fc_insert(s, y);
		// s->flr.rayDirX0 = s->p.dirX - s->p.planeX;
		// s->flr.rayDirY0 = s->p.dirY - s->p.planeY;
		// s->flr.rayDirX1 = s->p.dirX + s->p.planeX;
		// s->flr.rayDirY1 = s->p.dirY + s->p.planeY;
		// s->flr.center = y - s->minfo.s_height / 2;
		// s->flr.posZ = 0.5 * s->minfo.s_height;
		// s->flr.rowDistance = s->flr.posZ / s->flr.center;
		// s->flr.floorStepX = s->flr.rowDistance * (s->flr.rayDirX1 - s->flr.rayDirX0) / s->minfo.s_width;
		// s->flr.floorStepY = s->flr.rowDistance * (s->flr.rayDirY1 - s->flr.rayDirY0) / s->minfo.s_width;
		// s->flr.floorX = s->p.posX + s->flr.rowDistance * s->flr.rayDirX0;
		// s->flr.floorY = s->p.posY + s->flr.rowDistance * s->flr.rayDirY0;

		while (i < s->minfo.s_width)
		{
			s->flr.tx = (int)(TEX_WIDTH * (s->flr.floorX - (int)(s->flr.floorX))) & (TEX_WIDTH - 1);
			s->flr.ty = (int)(TEX_HEIGHT * (s->flr.floorY - (int)(s->flr.floorY))) & (TEX_HEIGHT - 1);
			s->flr.floorX += s->flr.floorStepX;
			s->flr.floorY += s->flr.floorStepY;
			fc_kind(s, y, i);
			// if (s->minfo.f_kind)
			// {   
			// 	s->tex.floorTexture = 8;
			// 	s->tex.color = s->p.texture[s->tex.floorTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
			// 	s->tex.color = (s->tex.color >> 1) & 8355711;
			// }
			// else
			// 	s->tex.color = s->minfo.floor;

			// s->img.data[y * s->minfo.s_width + i] = s->tex.color;

			// if (s->minfo.c_kind)
			// {
			// 	s->tex.ceilingTexture = 10;
			// 	s->tex.color = s->p.texture[s->tex.ceilingTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
			// 	s->tex.color = (s->tex.color >> 1) & 8355711;
			// }
			// else
			// 	s->tex.color = s->minfo.ceiling;

			// s->img.data[(s->minfo.s_height - y - 1) * s->minfo.s_width + i] = s->tex.color;
			i++;
		}
		y++;
		i = 0;
	}
}
