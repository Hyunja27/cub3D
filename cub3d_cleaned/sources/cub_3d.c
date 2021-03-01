/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 14:34:43 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char *av[])
{
	t_set	set;

	if (init_basic(&set, ac, av))
	{
		printf("\n\nWell.. you give me 3 args, But last argument is Not \
		'--save'.. what are you want..?\n\n\n");
		return (1);
	}
	if (map_parse(&set, set.map_path))
		return (1);
	if (!check_map(&set))
	{
		printf("\n\nI Got Map data, but it has Map Error! check tmp_map\n\n\n");
		return (0);
	}
	if (!(set.p.zBuffer = malloc(sizeof(double) * set.minfo.s_width)))
		return (-1);
	sound_bgm();
	sound_effect(1);
	make_window(&set);
	load_tex(&set);
	mlx_hook(set.win_ptr, KEYPRESS, 0, key_press, &set);
	mlx_hook(set.win_ptr, KEYRELEASE, 0, key_release, &set);
	mlx_loop_hook(set.mlx_ptr, &main_loop, &set);
	mlx_loop(set.mlx_ptr);
	free_memory(&set);
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
