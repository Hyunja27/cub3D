/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:05:36 by spark             #+#    #+#             */
/*   Updated: 2021/02/26 17:12:15 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../mlx_beta/mlx.h"

void		get_max_screen(t_set *s)
{
	int	max_x;
	int	max_y;

	mlx_get_screen_size(s->img.img_ptr, &max_x, &max_y);
	if (s->minfo.s_width > max_x)
		s->minfo.s_width = max_x;
	if (s->minfo.s_height > max_y)
		s->minfo.s_height = max_y;
}
