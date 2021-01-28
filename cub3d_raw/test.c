/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:39:29 by spark             #+#    #+#             */
/*   Updated: 2021/01/10 23:37:26 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#include "include/cub3d.h" 

t_set	set;

//based on referrence
void  my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
  int *dst;

 // dst = data->data + (y * data->size_l + x * (data->bpp / 8));
  dst = data->data + (y * WIDTH + x );
  *(unsigned int*)dst = color;
}

void	draw_square(t_img set, int start, int color)
{
	int		i = 0;
	int		j = 0;
	
	while (j < BOX_SIZE)
	{
		i = 0;
		while (i < BOX_SIZE)
		{
			set.data[start + i] = color;
			i++;
		}
		start += WIDTH;
		j++;
	}
}

void	draw_cross_line(t_img set, int start, int color)
{
	int		i = 0;

	while ((((start + i) % WIDTH) != 0))
		set.data[start + i++] = color;
	i = 0;
	while ((((start - i) % WIDTH) != 0))
		set.data[start - i++] = color;
	i = 0;
	while (((i * WIDTH) <= WIDTH * HEIGHT) && (((start + (i * WIDTH)) % WIDTH) != 0))
		set.data[start + (i++ * WIDTH)] = color;
	i = 0;
	while (((start - (i * WIDTH)) >= 0) && (((start + (i * WIDTH)) % WIDTH) != 0))
		set.data[start - (i++ * WIDTH)] = color;
}

// void	draw_strange_line(t_img set, int start, int color)
// {
// 	int		i;
// 	int		degree;

// 	i = 0;
// 	degree = 1;
// 	while (((start + (i * WIDTH) + (i + degree)) <= WIDTH * HEIGHT) && (((start + (i * WIDTH) + (i + degree)) != 0)))
// 	{
// 		set.data[start + (i * WIDTH) + (i + degree)] = color;
// 		i++;
// 	}
// 	i = 0;
// 	// while (((start - (i * WIDTH) - (i * degree) ) >= 0) && ((start - (i * WIDTH) - (i * degree) != 0)))
// 	// {
// 	// 	set.data[start - (i * WIDTH) - (i * degree)] = color;
// 	// 	i++;
// 	// }
// }

void parse_draw_line(t_img set, int map[20][20],int color)
{
	int i;
	int j;
	int point;

	i = 0;
	j = 0;
	point = 0;
	while (i < COLS)
	{
		while (j < ROWS)
		{
			if (map[i][j] == 1)
			{
				point = (i * (WIDTH * BOX_SIZE)) + (j * BOX_SIZE);
				if (point > WIDTH)
					draw_cross_line(set, point, color);
			}
			j++;
		}
		j = 0;
		i++;
	}
	// draw_strange_line(set, 5000, 0xffffff);
}

void parse_draw_map(t_img set, int map[20][20],int color)
{
	int i;
	int j;
	int point;

	i = 0;
	j = 0;
	point = 0;
	
	while (i < COLS)
	{
		while (j < ROWS)
		{
			point = (i * (WIDTH * BOX_SIZE)) + (j * BOX_SIZE);
			//draw_square(set, point, 0);
			if (map[i][j] == 1)
			{
				point = (i * (WIDTH * BOX_SIZE)) + (j * BOX_SIZE);
				draw_square(set, point, color);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int key_press(int keycode, t_set *set)
{
  if (keycode == ESC_KEY)
  {
    mlx_destroy_window(set->mlx_ptr, set->win_ptr);
    exit(0);
  }
  if (keycode == LEFT_KEY)
    set->left = 1;
  if (keycode == RIGHT_KEY)
    set->right = 1;
  if (keycode == UP_KEY)
    set->up = 1;
  if (keycode == DOWN_KEY)
    set->down = 1;
  return (0);
}

int key_release(int keycode, t_set *set)
{
  if (keycode == LEFT_KEY)
    set->left = 0;
  if (keycode == RIGHT_KEY)
    set->right = 0;
  if (keycode == UP_KEY)
    set->up = 0;
  if (keycode == DOWN_KEY)
    set->down = 0;
  return (0);
}

int	move(t_set *set)
{
	static int position_x = BOX_SIZE;
	static int position_y = BOX_SIZE;
	int i;
	int j;
	int k;
	
	if (set->up == 1 && position_y > 0)
	{
		position_y -= 3;
		printf("X = %d / Y = %d\n\n", position_x, position_y);
	}
	else if (set->down == 1 && position_y + BOX_SIZE < HEIGHT)
	{
		position_y += 3;
		printf("X = %d / Y = %d\n\n", position_x, position_y);
	}
	else if (set->left == 1 && position_x > 0)
	{
		position_x -= 3;
		printf("X = %d / Y = %d\n\n", position_x, position_y);
	}
	else if (set->right == 1 && position_x + BOX_SIZE < WIDTH)
	{
		position_x += 3;
		printf("X = %d / Y = %d\n\n", position_x, position_y);
	}
	for(int a = 0; a < HEIGHT * WIDTH; a++)
		set->img.data[a] = 0;
	for (i = position_x, k = 50; i < position_x + 25; i++, k -= 2)
		{
			for (j = (position_y) + k; j <=  (position_y) + 50; j++)
			my_mlx_pixel_put(&set->img, i, j, 0x0000FF00);
		}
	for (i = position_x + 25, k = 0; i < position_x + 50; i++, k += 2)
		{
			for (j = (position_y) + k; j <=  (position_y) + 50; j++)
			my_mlx_pixel_put(&set->img, i, j, 0x0000FF00);
		}
	return (0);
}

int	main_loop(t_set *set)
{
	move(set);
	parse_draw_map(set->img, map, 0xcc82cc);
	parse_draw_line(set->img, map, 0xffe6c1);
	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
	return (0);
}

int main(int ac, char *av[])
{
	void	*image;
	int		i;
	int		j;
	int		k;
	int		img_width;
	int		img_height;
	int		position_x;
	int		position_y;
	
	set.up = 0;
	set.left = 0;
	set.right = 0;
	set.down = 0;
	
	set.mlx_ptr = mlx_init();
	set.win_ptr = mlx_new_window(set.mlx_ptr, WIDTH, HEIGHT, "cub3D_window_making_test");
	//set.img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./images/white_back.xpm", &img_width, &img_height);
	// mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
	set.img.img_ptr = mlx_new_image(set.mlx_ptr, WIDTH, HEIGHT);
	set.img.data = (int*)mlx_get_data_addr(set.img.img_ptr, &set.img.bpp, &set.img.size_l, &set.img.endian);
	// parse_draw_map(set.img, map, 0xcc82cc);
	// parse_draw_line(set.img, map, 0xffe6c1);	

// //based on refference
// 	for (i = position_x, k = 50; i < position_x + 25; i++, k -= 2)
//   {
//     for (j = (position_y) + k; j <=  (position_y) + 50; j++)
//       my_mlx_pixel_put(&set, i, j, 0x0000FF00);
//   }
// 	for (i = position_x + 25, k = 0; i < position_x + 50; i++, k += 2)
//   {
//     for (j = (position_y) + k; j <=  (position_y) + 50; j++)
//       my_mlx_pixel_put(&set, i, j, 0x0000FF00);
// //   }
 	//mlx_put_image_to_window(set.mlx_ptr, set.win_ptr, set.img.img_ptr, 0, 0);
	
	// mlx_key_hook(win_ptr, &press_all_key, win_ptr);

	mlx_hook(set.win_ptr, KeyPress, 0, &key_press, &set);
	mlx_hook(set.win_ptr, KeyRelease, 0, key_release, &set);

	mlx_loop_hook(set.mlx_ptr, main_loop, &set);
	mlx_loop(set.mlx_ptr);
	
	return (0);
}
