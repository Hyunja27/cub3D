/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:58:09 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 17:15:03 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_loop(t_set *set)
{
	clean_screen(set);
	carl_ray(set);
	sprite_cast(set);
	parse_draw_lifebar(set);
	time_move(set);
	if (set->life <= 0)
	{
		printf("\nWoo...So bad control...try to nice move! :(\n\n");
		key_press(ESC_KEY, set);
	}
	if (set->map1 == 1)
		parse_draw_map(set);
	key_action(set);
	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
	if (set->save_flag)
	{
		make_bmp(set);
		printf("\n\nbmp file is made by your command! enjoy it! :)\n\n\n");
		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		exit(0);
	}
	return (0);
}
