/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_2d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:58:31 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 17:57:29 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_set *set, int x, int y, int corl)
{
	int i;
	int j;

	x *= MAP_BOX_SIZE;
	y *= MAP_BOX_SIZE;
	i = 0;
	while (i < MAP_BOX_SIZE)
	{
		j = 0;
		while (j < MAP_BOX_SIZE)
		{
			set->img.data[(x + i) * set->minfo.s_width + y + j] = corl;
			j++;
		}
		i++;
	}
}

void	draw_all_rect(t_set *set)
{
	int i;
	int j;

	i = 0;
	while (i < set->minfo.m_height)
	{
		j = 0;
		while (j < set->minfo.m_width)
		{
			if (set->map2[i][j] == 1 || set->map2[i][j] == 9)
				draw_rect(set, i, j, 0xFFFFFF);
			else if (set->map2[i][j] == 2)
				draw_rect(set, i, j, 0xAAFFAA);
			else if (set->map2[i][j] == 3)
				draw_rect(set, i, j, 0xABDADA);
			j++;
		}
		i++;
	}
}

void	parse_draw_map(t_set *s)
{
	int i;
	int j;
	int a;
	int b;

	draw_all_rect(s);
	i = s->p.posX * MAP_BOX_SIZE;
	j = s->p.posY * MAP_BOX_SIZE;
	a = -1;
	while (++a < 2)
	{
		b = 0;
		while (b < 3)
		{
			s->img.data[(i + a) * s->minfo.s_width + (j + b)] = 0xff0000;
			b++;
		}
	}
}
