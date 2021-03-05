/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:30:11 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:24:00 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_basic_2(t_set *set)
{
	set->minfo.num_sprite = 0;
	set->p.rspd = 0.03;
	set->p.movespeed = 0.04;
	set->up = 0;
	set->left = 0;
	set->right = 0;
	set->down = 0;
	set->p.hit = 0;
	set->mlx_ptr = mlx_init();
	set->life = 50;
	set->collision = 0;
	set->jump = 0;
	set->jump_end = 0;
	set->updown = 0;
	set->p.secret = 0;
	set->door = 0;
	set->door_end = 0;
}

int		init_basic(t_set *set, int ac, char *av[])
{
	init_basic_2(set);
	if (ac > 3 || ac == 1)
	{
		error_msg("Wrong Input!");
		return (1);
	}
	if (ac == 2)
		set->map_path = av[1];
	else if (ac == 3)
	{
		set->map_path = av[1];
		if (!ft_strnstr(av[2], "--save", 6))
			return (1);
		else
			set->save_flag = 1;
	}
	return (0);
}
