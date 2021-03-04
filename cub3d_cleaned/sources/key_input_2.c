/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:05:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/04 20:42:40 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press_2(int keycode, t_set *set)
{
	if (keycode == LEFT_KEY)
		set->left = 1;
	if (keycode == RIGHT_KEY)
		set->right = 1;
	if (keycode == UP_KEY)
		set->up = 1;
	if (keycode == DOWN_KEY)
		set->down = 1;
	if (keycode == SPACE_KEY)
		set->space = 1;
	if (keycode == LEFT_ARROW)
		set->left_arrow = 1;
	if (keycode == RIGHT_ARROW)
		set->right_arrow = 1;
	if (keycode == UP_ARROW)
		set->up_arrow = 1;
	if (keycode == DOWN_ARROW)
		set->down_arrow = 1;
	return (0);
}

int			key_press(int keycode, t_set *set)
{
	if (keycode == ESC_KEY)
	{
		system("killall afplay");
		sound_effect(2);
		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		free_memory(set);
		exit(0);
	}
	if (keycode == P_KEY)
	{
		make_bmp(set);
		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		free_memory(set);
		exit(0);
	}
	return (key_press_2(keycode, set));
}

int			key_release_2(int keycode, t_set *set)
{
	if (keycode == LEFT_ARROW)
		set->left_arrow = 0;
	if (keycode == RIGHT_ARROW)
		set->right_arrow = 0;
	if (keycode == UP_KEY)
		set->up = 0;
	if (keycode == DOWN_KEY)
		set->down = 0;
	if (keycode == SPACE_KEY)
		set->space = 0;
	if (keycode == LEFT_KEY)
		set->left = 0;
	if (keycode == RIGHT_KEY)
		set->right = 0;
	if (keycode == UP_ARROW)
		set->up_arrow = 0;
	if (keycode == DOWN_ARROW)
		set->down_arrow = 0;
	return (0);
}

int			key_release(int keycode, t_set *set)
{
	if (keycode == Q_KEY)
	{
		if (set->q_action == 0)
			set->q_action = 1;
		else
			set->q_action = 0;
	}
	if (keycode == M_KEY)
	{
		if (set->map1 == 0)
			set->map1 = 1;
		else
			set->map1 = 0;
	}
	return (key_release_2(keycode, set));
}

int			key_exit(t_set *set)
{
	system("killall afplay");
	sound_effect(2);
	mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
	mlx_destroy_window(set->mlx_ptr, set->win_ptr);
	free_memory(set);
	exit(0);
}
