/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:09:23 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_check(t_set *s)
{
	s->p.raydiry = s->p.diry + s->p.planey * s->p.camerax;
	s->p.positionx = (int)s->p.posx;
	s->p.positiony = (int)s->p.posy;
	s->p.deltadistx = fabs(1 / s->p.raydirx);
	s->p.deltadisty = fabs(1 / s->p.raydiry);
	if (s->p.raydirx < 0)
	{
		s->p.stepx = -1;
		s->p.sidex = (s->p.posx - s->p.positionx) * s->p.deltadistx;
	}
	else
	{
		s->p.stepx = 1;
		s->p.sidex = (s->p.positionx + 1.0 - s->p.posx) * s->p.deltadistx;
	}
	if (s->p.raydiry < 0)
	{
		s->p.stepy = -1;
		s->p.sidey = (s->p.posy - s->p.positiony) * s->p.deltadisty;
	}
	else
	{
		s->p.stepy = 1;
		s->p.sidey = (s->p.positiony + 1.0 - s->p.posy) * s->p.deltadisty;
	}
}

void	hit_check(t_set *s)
{
	while (s->p.hit == 0)
	{
		if (s->p.sidex < s->p.sidey)
		{
			s->p.sidex += s->p.deltadistx;
			s->p.positionx += s->p.stepx;
			s->p.hit_side = 0;
		}
		else
		{
			s->p.sidey += s->p.deltadisty;
			s->p.positiony += s->p.stepy;
			s->p.hit_side = 1;
		}
		if (s->map2[s->p.positionx][s->p.positiony] == 1 || \
		(s->p.positionx == s->p.hid_x && s->p.positiony == \
		s->p.hid_y && s->door != 32))
		{
			s->p.hit = 1;
			if (s->p.positionx == s->p.hid_x && s->p.positiony == s->p.hid_y)
				s->p.secret = 1;
		}
	}
	hit_check_2(s);
}

void	ray_insert(t_set *s)
{
	s->cr.line_screenheight = (int)(s->minfo.s_height / s->p.perpwalldist);
	s->cr.draw_start = -s->cr.line_screenheight / 2 + s->minfo.s_height / 2;
	if (s->cr.draw_start < 0)
		s->cr.draw_start = 0;
	s->cr.draw_end = s->cr.line_screenheight / 2 + s->minfo.s_height / 2;
	if (s->cr.draw_end >= s->minfo.s_height)
		s->cr.draw_end = s->minfo.s_height - 1;
	if (s->p.hit_side == 0)
		s->cr.wallx = s->p.posy + s->p.perpwalldist * s->p.raydiry;
	else
		s->cr.wallx = s->p.posx + s->p.perpwalldist * s->p.raydirx;
	s->cr.wallx -= floor(s->cr.wallx);
	s->tex.texx = (int)(s->cr.wallx * (double)TEX_WIDTH);
	if (s->p.hit_side == 0 && s->p.raydirx > 0)
		s->tex.texx = TEX_WIDTH - s->tex.texx - 1;
	if (s->p.hit_side == 1 && s->p.raydiry < 0)
		s->tex.texx = TEX_WIDTH - s->tex.texx - 1;
	s->p.step = 1.0 * TEX_HEIGHT / s->cr.line_screenheight;
	s->p.texture_pos = (s->cr.draw_start - s->minfo.s_height / 2 + \
	s->cr.line_screenheight / 2) * s->p.step;
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
		if (s->p.raydiry > 0)
			s->tex.texture_kind = 2;
		else
			s->tex.texture_kind = 3;
	}
	else if (s->p.hit_side == 0)
	{
		if (s->p.raydirx > 0)
			s->tex.texture_kind = 0;
		else
			s->tex.texture_kind = 1;
	}
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
		s->p.camerax = 2 * x / w - 1;
		s->p.raydirx = s->p.dirx + s->p.planex * s->p.camerax;
		side_check(s);
		i = s->cr.draw_start - 1;
		while (++i < s->cr.draw_end)
			carl_ray_2(s, &tmp, i, x);
		s->p.zBuffer[x] = s->p.perpwalldist;
	}
}
