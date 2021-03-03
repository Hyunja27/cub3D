/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 19:51:48 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_check(t_set *s)
{
	s->p.raydirY = s->p.dirY + s->p.planeY * s->p.cameraX;
	s->p.positionX = (int)s->p.posX;
	s->p.positionY = (int)s->p.posY;
	s->p.deltadistX = fabs(1 / s->p.raydirX);
	s->p.deltadistY = fabs(1 / s->p.raydirY);
	if (s->p.raydirX < 0)
	{
		s->p.stepX = -1;
		s->p.sideX = (s->p.posX - s->p.positionX) * s->p.deltadistX;
	}
	else
	{
		s->p.stepX = 1;
		s->p.sideX = (s->p.positionX + 1.0 - s->p.posX) * s->p.deltadistX;
	}
	if (s->p.raydirY < 0)
	{
		s->p.stepY = -1;
		s->p.sideY = (s->p.posY - s->p.positionY) * s->p.deltadistY;
	}
	else
	{
		s->p.stepY = 1;
		s->p.sideY = (s->p.positionY + 1.0 - s->p.posY) * s->p.deltadistY;
	}
}

void	hit_check(t_set *s)
{
	while (s->p.hit == 0)
	{
		if (s->p.sideX < s->p.sideY)
		{
			s->p.sideX += s->p.deltadistX;
			s->p.positionX += s->p.stepX;
			s->p.hit_side = 0;
		}
		else
		{
			s->p.sideY += s->p.deltadistY;
			s->p.positionY += s->p.stepY;
			s->p.hit_side = 1;
		}
		if (s->map2[s->p.positionX][s->p.positionY] == 1 || \
		(s->map2[s->p.positionX][s->p.positionY] == 9 && s->door != 32))
		{
			s->p.hit = 1;
			if (s->map2[s->p.positionX][s->p.positionY] == 9)
				s->p.secret = 1;
		}
	}
	if (s->p.hit_side == 0)
		s->p.perpwalldist = (s->p.positionX - s->p.posX + \
		(1 - s->p.stepX) / 2) / s->p.raydirX;
	else
		s->p.perpwalldist = (s->p.positionY - s->p.posY + \
		(1 - s->p.stepY) / 2) / s->p.raydirY;
}

void	ray_insert(t_set *s)
{
	s->cr.line_screenHeight = (int)(s->minfo.s_height / s->p.perpwalldist);
	s->cr.draw_start = -s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
	if (s->cr.draw_start < 0)
		s->cr.draw_start = 0;
	s->cr.draw_end = s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
	if (s->cr.draw_end >= s->minfo.s_height)
		s->cr.draw_end = s->minfo.s_height - 1;
	if (s->p.hit_side == 0)
		s->cr.wallX = s->p.posY + s->p.perpwalldist * s->p.raydirY;
	else
		s->cr.wallX = s->p.posX + s->p.perpwalldist * s->p.raydirX;
	s->cr.wallX -= floor(s->cr.wallX);
	s->tex.texX = (int)(s->cr.wallX * (double)TEX_WIDTH);
	if (s->p.hit_side == 0 && s->p.raydirX > 0)
		s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
	if (s->p.hit_side == 1 && s->p.raydirY < 0)
		s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
	s->p.step = 1.0 * TEX_HEIGHT / s->cr.line_screenHeight;
	s->p.texture_pos = (s->cr.draw_start - s->minfo.s_height / 2 + \
	s->cr.line_screenHeight / 2) * s->p.step;
}

void	side_check(t_set *s)
{
	step_check(s);
	hit_check(s);
	ray_insert(s);
	if (s->p.secret == 1)
	{
		s->tex.texture_kind = 7;
		s->p.secret = 0;
	}
	else if (s->p.hit_side == 1)
	{
		if (s->p.raydirY > 0)
			s->tex.texture_kind = 2;
		else
			s->tex.texture_kind = 3;
	}
	else if (s->p.hit_side == 0)
	{
		if (s->p.raydirX > 0)
			s->tex.texture_kind = 0;
		else
			s->tex.texture_kind = 1;
	}
}

void	secret_check(t_set *s)
{
	int		tmp;

	tmp = (TEX_HEIGHT) * (s->tex.texY - (s->door * 2)) + s->tex.texX;
	// tmp = (tmp < 0) ? 0 : tmp;
	// tmp = (tmp >= s->minfo.s_height) ?  s->minfo.s_height : tmp;
	
	s->tex.color = s->p.texture[s->tex.texture_kind][tmp];
	
	if (s->door == 31)
		s->map2[4][21] = 0;
	else 
		s->map2[4][21] = 9;

}

void	carl_ray(t_set *s)
{
	int		x;
	int		i;
	double	w;
	int		tmp;

	w = s->minfo.s_width;
	x = -1;
	i = 0;
	carl_fc(s);
	while (++x < (int)w)
	{
		s->p.hit = 0;
		s->p.cameraX = 2 * x / w - 1;
		s->p.raydirX = s->p.dirX + s->p.planeX * s->p.cameraX;
		side_check(s);
		i = s->cr.draw_start - 1;
		while (++i < s->cr.draw_end)
		{
			s->tex.texY = (int)s->p.texture_pos & (TEX_HEIGHT - 1);
			s->p.texture_pos += s->p.step;
			if (s->tex.texture_kind == 7)
			{
				secret_check(s);
			// 	s->tex.color = s->p.texture[s->tex.texture_kind]\
			// [(TEX_HEIGHT) * (s->tex.texY - (s->updown * 2)) + s->tex.texX];
			//(TEX_HEIGHT) * s->tex.texY + s->tex.texX + (s->updown * 2)
			}
			else
				s->tex.color = s->p.texture[s->tex.texture_kind]\
			[TEX_HEIGHT * s->tex.texY + s->tex.texX];
			tmp = ((i - (s->updown * 2) + s->jump) * s->minfo.s_width + x);
			tmp = tmp < 0 ? 0 : tmp;
			s->img.data[tmp] = s->tex.color;
		}
		s->p.zBuffer[x] = s->p.perpwalldist;
	}
}
