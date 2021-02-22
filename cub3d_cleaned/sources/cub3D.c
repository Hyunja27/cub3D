/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/02/23 01:11:17 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char *av[])
{
	int i;
	int j;
	t_set set;

	if (ac > 3 || ac == 1)
	{
		error_msg("Wrong Input!");
		return (1);
	}
	if (ac == 2)
		set.map_path = av[1];
	else if (ac == 3)
	{
		set.map_path = av[1];
		if (!ft_strnstr(av[2], "--save", 6))
			return (0);
		else
			set.save_flag = 1;
	}
	printf("map_path : %s\n", set.map_path);
	
	set.p.rspd = 0.02;
	set.p.movespeed = 0.06;

	set.up = 0;
	set.left = 0;
	set.right = 0;
	set.down = 0;
	set.p.hit = 0;

	set.mlx_ptr = mlx_init();

	i = 0;
	j = 0;
	
	map_parse(&set, set.map_path);
	if (!check_map(&set))
		printf("Map Error\n");
	
	i = 0;
	if (!(set.p.zBuffer = malloc(sizeof(double) * set.minfo.s_width)))
		return (-1);
	make_window(&set);
	load_tex(&set);
	mlx_hook(set.win_ptr, KeyPress, 0, key_press, &set);
	mlx_hook(set.win_ptr, KeyRelease, 0, key_release, &set);
	mlx_loop_hook(set.mlx_ptr, &main_loop, &set);
	mlx_loop(set.mlx_ptr);	

	
	while (i < set.minfo.m_height)
		free(set.map2[i++]);
	free(set.map2);
	free(set.S_tex);
	free(set.W_tex);
	free(set.N_tex);
	free(set.E_tex);
	free(set.SPR_tex);
	free(set.minfo.no_path);
	free(set.minfo.so_path);
	free(set.minfo.we_path);
	free(set.minfo.ea_path);
	free(set.minfo.sp_path);
	if (!set.minfo.f_path)
		free(set.minfo.f_path);
	if (!set.minfo.c_path)
		free(set.minfo.c_path);
	free(set.p.zBuffer);
	free(set.spr.sprt);
	free(set.spr.spriteDistance);
	free(set.spr.spriteOrder);
	return (0);
}


	// while(i < set.minfo.num_sprite)
	// {
	// 	printf("\n%f / %f",set.spr.sprt[i].x,set.spr.sprt[i].y);
	// 	i++;
	// }
	// i = 0;
	// printf("s_width : %d\n", set.minfo.s_width);
	// printf("s_height : %d\n", set.minfo.s_height);
	// printf("no_path : %s\n", set.minfo.no_path);
	// printf("so_path : %s\n", set.minfo.so_path);
	// printf("we_path : %s\n", set.minfo.we_path);
	// printf("ea_path : %s\n", set.minfo.ea_path);
	// printf("s_path : %s\n", set.minfo.sp_path);
	// printf("floor : %d\n", set.minfo.floor);
	// printf("ceiling : %d\n", set.minfo.ceiling);
	// printf("floor_path : %s\n", set.minfo.f_path);
	// printf("ceiling_path : %s\n", set.minfo.c_path);

	// printf("m_height : %d\n", set.minfo.m_height);
	// printf("m_width : %d\n", set.minfo.m_width);
	// printf("num_sprite : %d\n", set.minfo.num_sprite);
	// for (int i = 0; i < set.minfo.m_height; i++)
	// {
	// 	for (int j = 0; j < set.minfo.m_width; j++)
	// 		printf("%3d", set.map2[i][j]);
	// 	printf("\n");
	// }
	// printf("*\n");
