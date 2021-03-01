/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_2d_lifebar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:58:31 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 16:27:01 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lifebar(t_set *set, int x, int y, int corl)
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
			set->img.data[(x + set->minfo.s_height - 80 + i) * set->minfo.s_width + y + 20 + j] = corl;
			j++;
		}
		i++;
	}
}

void	draw_all_rect_lifebar(t_set *set)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		if (i == 0 || i == 7)
		{
			while (j < 50)
			{
				draw_lifebar(set, i, j, 0x000000);
				j++;
			}
		}
		draw_lifebar(set, i, 0, 0x000000);
		draw_lifebar(set, i, 50, 0x000000);
		i++;
	}
}

void	draw_life(t_set *set)
{
	int i;
	int j;

	i = 1;
	while (i < 7)
	{
		j = 1;
			while (j < (int)set->life)
			{
				draw_lifebar(set, i, j, 0xFF0000);
				j++;
			}
		// draw_lifebar(set, i, 0, 0xFFFFFF);
		// draw_lifebar(set, i, 50, 0xFFFFFF);
		i++;
	}
}

void	parse_draw_lifebar(t_set *s)
{
	draw_all_rect_lifebar(s);
	draw_life(s);
}
