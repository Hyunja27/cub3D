/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_arrange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:53:02 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 22:03:27 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	arrange_sprite(t_set *s)
{
	int		tmp;
	double	dis_tmp;
	double	max;
	int		i;
	int		j;

	i = -1;
	while (++i < s->minfo.num_sprite - 1)
	{
		max = s->spr.spriteDistance[i];
		j = i;
		while (++j < s->minfo.num_sprite)
		{
			if (max <= s->spr.spriteDistance[j])
			{
				max = s->spr.spriteDistance[j];
				tmp = s->spr.spriteOrder[i];
				s->spr.spriteOrder[i] = s->spr.spriteOrder[j];
				s->spr.spriteOrder[j] = tmp;
				dis_tmp = s->spr.spriteDistance[i];
				s->spr.spriteDistance[i] = s->spr.spriteDistance[j];
				s->spr.spriteDistance[j] = dis_tmp;
			}
		}
	}
}
