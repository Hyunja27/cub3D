/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:52:03 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 22:54:32 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		make_window(t_set *s)
{
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->minfo.s_width, \
		s->minfo.s_height, "Cub3D_By_Spark");
	s->img.img_ptr = mlx_new_image(s->mlx_ptr, s->minfo.s_width, \
		s->minfo.s_height);
	s->img.data = (int *)mlx_get_data_addr(s->img.img_ptr, &s->img.bpp, \
		&s->img.size_l, &s->img.endian);
}

void		clean_screen(t_set *s)
{
	int i;

	i = 0;
	while (i <= s->minfo.s_height * s->minfo.s_width)
		s->img.data[i++] = 0;
}
