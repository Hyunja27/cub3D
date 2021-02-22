/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:51:24 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 22:22:43 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "cub3d_macro.h"
#include "cub3d_struct.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	draw_rect(t_set *set, int x, int y, int corl);
void	draw_all_rect(t_set *set);
void	parse_draw_map(t_set *s);

void	put_bmp_info(t_bmp *m, t_set *s);
t_bmp	make_bmp(t_set *s);

void	arrange_sprite(t_set *s);
int		key_press(int keycode, t_set *set);
int		key_release(int keycode, t_set *set);
void	key_action_2(t_set *s);
void	key_action(t_set *s);

#endif
