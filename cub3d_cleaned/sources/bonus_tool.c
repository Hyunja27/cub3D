/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:55:00 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 21:24:10 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	secret_check(t_set *s)
{
	int		tmp;

	tmp = (TEX_HEIGHT) * (s->tex.texY) + s->tex.texX - (s->door * 2);
	s->tex.color = s->p.texture[s->tex.texture_kind][tmp];
	if (s->door == 28)
		s->map2[s->p.hid_x][s->p.hid_y] = 0;
	else
		s->map2[s->p.hid_x][s->p.hid_y] = 9;
}

void	updown_protect(t_set *s)
{
	if (s->updown > s->minfo.s_height / 2)
		s->updown = s->minfo.s_height / 2;
	if (-s->updown > (s->minfo.s_height / 2))
		s->updown = -s->minfo.s_height / 2;
}

int		make_darker(int color, int size)
{
	int	r;
	int	g;
	int	b;

	b = color & 0X0000FF;
	g = (color >> 8) & 0X0000FF;
	r = (color >> 16) & 0X0000FF;
	size = size < 0 ? 0 : size;
	b -= size;
	g -= size;
	r -= size;
	b = b > 0 ? b : 0;
	g = g > 0 ? g : 0;
	r = r > 0 ? r : 0;
	return ((r * 256 * 256) + (g * 256) + b);
}
