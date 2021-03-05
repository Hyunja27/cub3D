/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_arrange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:53:02 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 15:42:17 by spark            ###   ########.fr       */
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
		max = s->spr.spritedistance[i];
		j = i;
		while (++j < s->minfo.num_sprite)
		{
			if (max <= s->spr.spritedistance[j])
			{
				max = s->spr.spritedistance[j];
				tmp = s->spr.spriteorder[i];
				s->spr.spriteorder[i] = s->spr.spriteorder[j];
				s->spr.spriteorder[j] = tmp;
				dis_tmp = s->spr.spritedistance[i];
				s->spr.spritedistance[i] = s->spr.spritedistance[j];
				s->spr.spritedistance[j] = dis_tmp;
			}
		}
	}
}
