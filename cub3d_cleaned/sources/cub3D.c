/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/02/23 00:27:05 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void carl_ray(t_set *s)
// {
// 	int x;
// 	int y;
// 	int i;
// 	double w;

// 	w = s->minfo.s_width;
// 	x = 0;
// 	y = 0;
// 	i = 0;

// 	while (y < s->minfo.s_height)
// 	{
// 		s->flr.rayDirX0 = s->p.dirX - s->p.planeX;
// 		s->flr.rayDirY0 = s->p.dirY - s->p.planeY;
// 		s->flr.rayDirX1 = s->p.dirX + s->p.planeX;
// 		s->flr.rayDirY1 = s->p.dirY + s->p.planeY;
// 		s->flr.center = y - s->minfo.s_height / 2;
// 		s->flr.posZ = 0.5 * s->minfo.s_height;
// 		s->flr.rowDistance = s->flr.posZ / s->flr.center;
// 		s->flr.floorStepX = s->flr.rowDistance * (s->flr.rayDirX1 - s->flr.rayDirX0) / s->minfo.s_width;
// 		s->flr.floorStepY = s->flr.rowDistance * (s->flr.rayDirY1 - s->flr.rayDirY0) / s->minfo.s_width;
// 		s->flr.floorX = s->p.posX + s->flr.rowDistance * s->flr.rayDirX0;
// 		s->flr.floorY = s->p.posY + s->flr.rowDistance * s->flr.rayDirY0;

// 		while (i < s->minfo.s_width)
// 		{
// 			s->flr.tx = (int)(TEX_WIDTH * (s->flr.floorX - (int)(s->flr.floorX))) & (TEX_WIDTH - 1);
// 			s->flr.ty = (int)(TEX_HEIGHT * (s->flr.floorY - (int)(s->flr.floorY))) & (TEX_HEIGHT - 1);
// 			s->flr.floorX += s->flr.floorStepX;
// 			s->flr.floorY += s->flr.floorStepY;
// 			if (s->minfo.f_kind)
// 			{
// 				s->tex.floorTexture = 8;
// 				s->tex.color = s->p.texture[s->tex.floorTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
// 				s->tex.color = (s->tex.color >> 1) & 8355711;
// 			}
// 			else
// 				s->tex.color = s->minfo.floor;

// 			s->img.data[y * s->minfo.s_width + i] = s->tex.color;

// 			if (s->minfo.c_kind)
// 			{
// 				s->tex.ceilingTexture = 10;
// 				s->tex.color = s->p.texture[s->tex.ceilingTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
// 				s->tex.color = (s->tex.color >> 1) & 8355711;
// 			}
// 			else
// 				s->tex.color = s->minfo.ceiling;

// 			s->img.data[(s->minfo.s_height - y - 1) * s->minfo.s_width + i] = s->tex.color;
// 			i++;
// 		}
// 		y++;
// 		i = 0;
// 	}

// 	while (x < (int)w)
// 	{
// 		s->p.hit = 0;

// 		s->p.cameraX = 2 * x / w - 1;
// 		s->p.raydirX = s->p.dirX + s->p.planeX * s->p.cameraX;
// 		s->p.raydirY = s->p.dirY + s->p.planeY * s->p.cameraX;

// 		s->p.positionX = (int)s->p.posX;
// 		s->p.positionY = (int)s->p.posY;

// 		s->p.deltadistX = fabs(1 / s->p.raydirX);
// 		s->p.deltadistY = fabs(1 / s->p.raydirY);

// 		if (s->p.raydirX < 0)
// 		{
// 			s->p.stepX = -1;
// 			s->p.sideX = (s->p.posX - s->p.positionX) * s->p.deltadistX;
// 		}
// 		else
// 		{
// 			s->p.stepX = 1;
// 			s->p.sideX = (s->p.positionX + 1.0 - s->p.posX) * s->p.deltadistX;
// 		}
// 		if (s->p.raydirY < 0)
// 		{
// 			s->p.stepY = -1;
// 			s->p.sideY = (s->p.posY - s->p.positionY) * s->p.deltadistY;
// 		}
// 		else
// 		{
// 			s->p.stepY = 1;
// 			s->p.sideY = (s->p.positionY + 1.0 - s->p.posY) * s->p.deltadistY;
// 		}

// 		while (s->p.hit == 0)
// 		{
// 			if (s->p.sideX < s->p.sideY)
// 			{
// 				s->p.sideX += s->p.deltadistX;
// 				s->p.positionX += s->p.stepX;
// 				s->p.hit_side = 0;
// 			}
// 			else
// 			{
// 				s->p.sideY += s->p.deltadistY;
// 				s->p.positionY += s->p.stepY;
// 				s->p.hit_side = 1;
// 			}
// 			if (s->map2[s->p.positionX][s->p.positionY] == 1)
// 				s->p.hit = 1;
// 		}

// 		if (s->p.hit_side == 0)
// 			s->p.perpwalldist = (s->p.positionX - s->p.posX + (1 - s->p.stepX) / 2) / s->p.raydirX;
// 		else
// 			s->p.perpwalldist = (s->p.positionY - s->p.posY + (1 - s->p.stepY) / 2) / s->p.raydirY;

// 		s->cr.line_screenHeight = (int)(s->minfo.s_height / s->p.perpwalldist);
// 		s->cr.draw_start = -s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
// 		if (s->cr.draw_start < 0)
// 			s->cr.draw_start = 0;
// 		s->cr.draw_end = s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
// 		if (s->cr.draw_end >= s->minfo.s_height)
// 			s->cr.draw_end = s->minfo.s_height - 1;
// 		if (s->p.hit_side == 0)
// 			s->cr.wallX = s->p.posY + s->p.perpwalldist * s->p.raydirY;
// 		else
// 			s->cr.wallX = s->p.posX + s->p.perpwalldist * s->p.raydirX;
// 		s->cr.wallX -= floor(s->cr.wallX);

// 		s->tex.texX = (int)(s->cr.wallX * (double)TEX_WIDTH);
// 		if (s->p.hit_side == 0 && s->p.raydirX > 0)
// 			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
// 		if (s->p.hit_side == 1 && s->p.raydirY < 0)
// 			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;

// 		s->p.step = 1.0 * TEX_HEIGHT / s->cr.line_screenHeight;
// 		s->p.texture_pos = (s->cr.draw_start - s->minfo.s_height / 2 + s->cr.line_screenHeight / 2) * s->p.step;

// 		if (s->p.hit_side == 1)
// 		{
// 			if (s->p.raydirY > 0)
// 				s->tex.texture_kind = 2;
// 			else
// 				s->tex.texture_kind = 3;
// 		}
// 		else if (s->p.hit_side == 0)
// 		{
// 			if (s->p.raydirX > 0)
// 				s->tex.texture_kind = 0;
// 			else
// 				s->tex.texture_kind = 1;
// 		}

// 		i = s->cr.draw_start;
// 		while (i < s->cr.draw_end)
// 		{
// 			s->tex.texY = (int)s->p.texture_pos & (TEX_HEIGHT - 1);
// 			s->p.texture_pos += s->p.step;
// 			s->tex.color = s->p.texture[s->tex.texture_kind][TEX_HEIGHT * s->tex.texY + s->tex.texX];
// 			s->img.data[i * s->minfo.s_width + x] = s->tex.color;
// 			i++;
// 		}
// 		s->p.zBuffer[x] = s->p.perpwalldist;
// 		x++;
// 	}
// }

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
