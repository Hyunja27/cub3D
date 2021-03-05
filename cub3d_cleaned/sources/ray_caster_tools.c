/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:26:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:08:34 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hit_check_2(t_set *s)
{
	if (s->p.hit_side == 0)
		s->p.perpwalldist = (s->p.positionx - s->p.posx + \
		(1 - s->p.stepx) / 2) / s->p.raydirx;
	else
		s->p.perpwalldist = (s->p.positiony - s->p.posy + \
		(1 - s->p.stepy) / 2) / s->p.raydiry;
}

void	carl_ray_2(t_set *s, int *tmp, int i, int x)
{
	s->tex.texy = (int)s->p.texture_pos & (TEX_HEIGHT - 1);
	s->p.texture_pos += s->p.step;
	if (s->tex.texture_kind == 7)
		secret_check(s);
	else
		s->tex.color = s->p.texture[s->tex.texture_kind]\
	[TEX_HEIGHT * s->tex.texy + s->tex.texx];
	s->tex.color = make_darker(s->tex.color, s->minfo.s_height \
	/ 2 - s->cr.line_screenheight * 2);
	*tmp = ((i - (s->updown * 2) + s->jump) * s->minfo.s_width + x);
	*tmp = *tmp < 0 ? 0 : *tmp;
	s->img.data[*tmp] = s->tex.color;
}
