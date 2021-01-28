/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:38:19 by spark             #+#    #+#             */
/*   Updated: 2021/01/13 13:31:36 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/raycaster.h"
#include "include/mlx.h"
#include "include/cub3d.h" 

t_point point;
t_set	set;

// void	draw_vertical(int x, int draw_start, int draw_end, int color)
// {
// 	int		y;

// 	y = draw_start * screenWidth;
// 	while (y <= draw_end * screenWidth)
// 	{
// 		set.img.data[y + x] = color;
// 		y += screenWidth;
// 		//mlx_pixel_put(set.mlx_ptr, set.win_ptr, x, y, color);
// 		//y++;
// 	}
// }

int key_press(int keycode, t_set *set)
{
	double	olddir_x;
	double	oldplane_x;
	
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
		exit(0);
	}
	if (keycode == UP_KEY)
	{
		if (!worldMap[(int)(point.pos_X + point.dir_X * point.movespeed)][(int)point.pos_Y])
			point.pos_X += point.dir_X * point.movespeed;
		if (!worldMap[(int)point.pos_X][(int)(point.pos_Y + point.dir_Y * point.movespeed)])
			point.pos_Y += point.dir_Y * point.movespeed;
	}
	if (keycode == DOWN_KEY)
	{
		if (!worldMap[(int)(point.pos_X - point.dir_X * point.movespeed)][(int)point.pos_Y])
			point.pos_X -= point.dir_X * point.movespeed;
		if (!worldMap[(int)point.pos_X][(int)(point.pos_Y - point.dir_Y * point.movespeed)])
			point.pos_Y -= point.dir_Y * point.movespeed;
	}
	if (keycode == RIGHT_KEY)
	{
		olddir_x = point.dir_X;
		point.dir_X = point.dir_X * cos(-point.rotspeed) - point.dir_Y * sin(-point.rotspeed);
		point.dir_Y = olddir_x * sin(-point.rotspeed) + point.dir_Y * cos(-point.rotspeed);
		oldplane_x = point.plane_X;
		point.plane_X = point.plane_X * cos(-point.rotspeed) - point.plane_Y * sin(-point.rotspeed);
		point.plane_Y = oldplane_x * sin(-point.rotspeed) + point.plane_Y * cos(-point.rotspeed);
	}
	if (keycode == LEFT_KEY)
	{
		olddir_x = point.dir_X;
		point.dir_X = point.dir_X * cos(point.rotspeed) - point.dir_Y * sin(point.rotspeed);
		point.dir_Y = olddir_x * sin(point.rotspeed) + point.dir_Y * cos(point.rotspeed);
		oldplane_x = point.plane_X;
		point.plane_X = point.plane_X * cos(point.rotspeed) - point.plane_Y * sin(point.rotspeed);
		point.plane_Y = oldplane_x * sin(point.rotspeed) + point.plane_Y * cos(point.rotspeed);
	}
	return (0);
}

void	make_window(t_set *set)
{
	set->win_ptr = mlx_new_window(set->mlx_ptr, screenWidth, screenHeight, "Raycaster Practice");
	set->img.img_ptr = mlx_new_image(set->mlx_ptr, screenWidth, screenHeight);
	set->img.data = (int*)mlx_get_data_addr(set->img.img_ptr, &set->img.bpp, &set->img.size_l, &set->img.endian);
}

void	carl_ray(t_set *set, t_point *p)
{
	int x;
	double w;
	int		i;
	int		texY;
	int		texX;
	double	wallX;
	int		texture_kind;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	
	x = 0;
	i = 0;
	w = screenWidth;

	// printf ("\nposition_x is : %d", p->position_X);
	// printf ("\nposition_y is : %d\n", p->position_Y);
	while (x < (int)w)
	{
		p->hit = 0;
		
		p->camera_X = 2 * x / w - 1;
		p->raydir_X = p->dir_X + p->plane_X * p->camera_X;
		p->raydir_Y = p->dir_Y + p->plane_Y * p->camera_X;

		p->position_X = (int)p->pos_X;
		p->position_Y = (int)p->pos_Y;
		
		p->deltadist_X = fabs(1 / p->raydir_X);
		p->deltadist_Y = fabs(1 / p->raydir_Y);

		if (p->raydir_X < 0)
		{
			p->step_X = -1;
			p->side_X = (p->pos_X - p->position_X) * p->deltadist_X;
		}
		else
		{
			p->step_X = 1;
			p->side_X = (p->position_X + 1.0 - p->pos_X) * p->deltadist_X;
		}
		if (p->raydir_Y < 0)
		{
			p->step_Y = -1;
			p->side_Y = (p->pos_Y - p->position_Y) * p->deltadist_Y;
		}
		else
		{
			p->step_Y = 1;
			p->side_Y = (p->position_Y + 1.0 - p->pos_Y) * p->deltadist_Y;
		}
		
		while (p->hit == 0)
		{
			if (p->side_X < p->side_Y)
			{
				p->side_X += p->deltadist_X;
				p->position_X += p->step_X;
				p->hit_side = 0;
			}
			else
			{
				p->side_Y += p->deltadist_Y;
				p->position_Y += p->step_Y;
				p->hit_side = 1;
			}
			if (worldMap[p->position_X][p->position_Y] > 0)
				p->hit = 1;
		}

		if (p->hit_side == 0)
			p->perpwalldist = (p->position_X - p->pos_X + (1 - p->step_X) / 2) / p->raydir_X;
		else
			p->perpwalldist = (p->position_Y - p->pos_Y + (1 - p->step_Y) / 2) / p->raydir_Y;
		
		line_height = (int)(screenHeight / p->perpwalldist);
		draw_start = -line_height / 2 + screenHeight / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + screenHeight / 2;
		if (draw_end >= screenHeight)
			draw_end = screenHeight - 1;
		
		// if (worldMap[p->position_X][p->position_Y] == 1)
		// 	color = CLR_LBL;
		// else if  (worldMap[p->position_X][p->position_Y] == 2)
		// 	color = CLR_ORG;
		// else if  (worldMap[p->position_X][p->position_Y] == 3)
		// 	color = CLR_CRD;
		// else if  (worldMap[p->position_X][p->position_Y] == 4)
		// 	color = CLR_KAK;
		// else if  (worldMap[p->position_X][p->position_Y] == 5)
		// 	color = CLR_DGR;
		// if (p->hit_side == 1)
		// 	color = color / 2;
		// draw_vertical(x, draw_start, draw_end, color);

		texture_kind = worldMap[p->position_X][p->position_Y] - 1;

		point.step = 1.0 * texHeight / line_height; 
		point.texture_pos = (draw_start - screenHeight / 2 + line_height / 2) * point.step;

		if (p->hit_side == 0)
			wallX = p->pos_Y + p->perpwalldist * p->raydir_Y;
		else
			wallX = p->pos_X + p->perpwalldist * p->raydir_X;
		wallX -= floor(wallX); 
			
		texX = (int)(wallX * (double)texWidth);
		if (p->hit_side == 0 && p->raydir_X > 0)
			texX = texWidth - texX - 1;
		if (p->hit_side == 1 && p->raydir_X < 0)
			texX = texWidth - texX - 1;
		
		i = draw_start;
		
		while (i < draw_end)
		{
			texY = (int)point.texture_pos & (texHeight - 1);
			point.texture_pos += point.step;
			color = point.texture[texture_kind][texHeight * texY + texX];
			if (p->hit_side == 1)
				color /= 2;
			set->img.data[i * screenWidth + x] = color;
			i++;
		}
		x++;
	}
}

void	clean_screen(t_set *set)
{
	int		i;

	i = 0;
	while (i <= screenHeight * screenWidth)
		set->img.data[i++] = 0;
}

int	main_loop(t_set *set)
{
	clean_screen(set);
	carl_ray(set, &point);
	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
	return (0);
}

int main(int ac, char *av[])
{
	int	i;
	int	j;

	point.pos_X = 22.0;
	point.pos_Y = 11.5;
	point.dir_X = -1;
	point.dir_Y = 0;
	point.plane_X = 0;
	point.plane_Y = 0.66;
	point.rotspeed = 0.05;
	point.movespeed = 0.05;

	set.up = 0;
	set.left = 0;
	set.right = 0;
	set.down = 0;
	point.hit = 0;

	set.mlx_ptr = mlx_init();

	i = 0;
	j = 0;

	while (i < texWidth)
	{
		j = 0;
		while (j < texHeight)
		{
			int xorcolor = (i * 256 / texWidth) ^ (j * 256 / texHeight);
			int ycolor = j * 256 / texHeight;
			int xycolor = j * 128 / texHeight + i * 128 / texWidth;
			point.texture[0][texWidth * j + i] = 65536 * 254 * (i != j && i != texWidth - j); //flat red texture with black cross
			point.texture[1][texWidth * j + i] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			point.texture[2][texWidth * j + i] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			point.texture[3][texWidth * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			point.texture[4][texWidth * j + i] = 256 * xorcolor; //xor green
			point.texture[5][texWidth * j + i] = 65536 * 192 * (i % 16 && j % 16); //red bricks
			point.texture[6][texWidth * j + i] = 65536 * ycolor; //red gradient
			point.texture[7][texWidth * j + i] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			j++;
		}
		i++;
	}

	// for(int x = 0; x < texWidth; x++)
    // {
    //     for(int y = 0; y < texHeight; y++)
    //     {
    //         int xorColor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
    //         int yColor = y * 256 / texHeight;
    //         int xyColor = y * 128 / texHeight + x * 128 / texWidth;
    //         point.texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); // flat red texture with black cross
    //         point.texture[1][texWidth * y + x] = xyColor + 256 * xyColor + 65536 * xyColor; // sloped greyscale
    //         point.texture[2][texWidth * y + x] = 256 * xyColor + 65536 * xyColor; // sloped yellow gradient
    //         point.texture[3][texWidth * y + x] = xorColor + 256 * xorColor + 65536 * xorColor; // xor greyscale
    //         point.texture[4][texWidth * y + x] = 256 * xorColor; // xor green
    //         point.texture[5][texWidth * y + x] = 65536 * 192 * (x % 16  && y % 16); //red bricks
    //         point.texture[6][texWidth * y + x] = 65536 * yColor; // red gradient
    //         point.texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; // flat grey texture
    //     }
    // }
	

	make_window(&set);
	mlx_hook(set.win_ptr, KeyPress, 0, key_press, &set);
	mlx_loop_hook(set.mlx_ptr, &main_loop, &set);
	mlx_loop(set.mlx_ptr);

	

	
	return (0);
}