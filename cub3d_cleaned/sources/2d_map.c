/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/01/28 12:45:06 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h" 

t_point point;
t_set	set;
t_sprite spt;

int		spriteOrder[numSprite];
int		spriteDistance[numSprite];

//based on referrence
void 	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
  int *dst;

 // dst = data->data + (y * data->size_l + x * (data->bpp / 8));
  dst = data->data + (y * screenWidth + x );
  *(unsigned int*)dst = color;
}

void	draw_square(t_img set, int start, int color)
{
	int		i = 0;
	int		j = 0;
	
	while (j < MAP_BOX_SIZE)
	{
		i = 0;
		while (i < MAP_BOX_SIZE)
		{
			set.data[start + i] = color;
			i++;
		}
		start += screenWidth;
		j++;
	}
}

void    arrange_Sprite(void)
{
    int     tmp;
    double  dis_tmp;
    double  max = 0;
    for(int i = 0; i < numSprite - 1; i++)
    {
        max = spriteDistance[i];
        for(int j = i + 1; j < numSprite; j++)
        {
            if (max <= spriteDistance[j])
            {
                max = spriteDistance[j];
                tmp = spriteOrder[i];
                spriteOrder[i] = spriteOrder[j];
                spriteOrder[j] = tmp;
                dis_tmp = spriteDistance[i];
                spriteDistance[i] = spriteDistance[j];
                spriteDistance[j] = dis_tmp;
            }
        }
    }
}

int		move(void)
{
	int i;
	int j;
	int k;
	int map2d_pos_X;
	int map2d_pos_Y;
	// for(int a = 0; a < screenHeight * screenWidth; a++)
	// 	set->img.data[a] = 0;

	map2d_pos_X = point.pos_X * MAP_BOX_SIZE;
	map2d_pos_Y = point.pos_Y * MAP_BOX_SIZE;
	for (i = (int)map2d_pos_X, k = 4; i < map2d_pos_X + 2; i++, k -= 2)
		{
			for (j = (map2d_pos_Y) + k; j <=  (map2d_pos_Y) + 4; j++)
			my_mlx_pixel_put(&set.img, j, i, 0x0000FF00);
		}
	for (i = map2d_pos_X + 2, k = 0; i < map2d_pos_X + 4; i++, k += 2)
		{
			for (j = (map2d_pos_Y) + k; j <=  (map2d_pos_Y) + 4; j++)
			my_mlx_pixel_put(&set.img, j, i, 0x0000FF00);
		}
	// draw_square(set, point.pos_X, 0x0000FF00);
	
	return (0);
}

void	draw_cross_line(t_img set, int start, int color)
{
	int		i = 0;

	while ((((start + i) % screenWidth) != 0))
		set.data[start + i++] = color;
	i = 0;
	while ((((start - i) % screenWidth) != 0))
		set.data[start - i++] = color;
	i = 0;
	while (((i * screenWidth) <= screenWidth * screenHeight) && (((start + (i * screenWidth)) % screenWidth) != 0))
		set.data[start + (i++ * screenWidth)] = color;
	i = 0;
	while (((start - (i * screenWidth)) >= 0) && (((start + (i * screenWidth)) % screenWidth) != 0))
		set.data[start - (i++ * screenWidth)] = color;
}

void	parse_draw_line(t_img set, int worldmap[24][24],int color)
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
			if (worldMap[i][j] == 1)
			{
				point = (i * (screenWidth * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
				// if (point > BOX_screenWidth)
				// 	draw_cross_line(set, point, color);
			}
			j++;
		}
		j = 0;
		i++;
	}
	// draw_strange_line(set, 5000, 0xffffff);
}

void	parse_draw_map(t_img set, int worldmap[24][24],int color)
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
			point = (i * (screenWidth * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
			//draw_square(set, point, 0);
			if (worldMap[i][j] != 0)
			{
				point = (i * (screenWidth * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
				draw_square(set, point, color);
			}
			j++;
		}
		j = 0;
		i++;
	}
	move();
}

int		key_press(int keycode, t_set *set)
{
	// double	olddir_x;
	// double	oldplane_x;

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

	// ===========================
	
	// 해당 부분을 메인 함수 루프 바디에서 실행해볼 것, 키 릴리즈와 프레스는 플래그만 바꿔주도록.
	// if (set->up == 1)
	// {
	// 	if (!worldMap[(int)(point.pos_X + point.dir_X * point.movespeed)][(int)point.pos_Y])
	// 		point.pos_X += point.dir_X * point.movespeed;
	// 	if (!worldMap[(int)point.pos_X][(int)(point.pos_Y + point.dir_Y * point.movespeed)])
	// 		point.pos_Y += point.dir_Y * point.movespeed;
	// }
	// if (set->down == 1)
	// {
	// 	if (!worldMap[(int)(point.pos_X - point.dir_X * point.movespeed)][(int)point.pos_Y])
	// 		point.pos_X -= point.dir_X * point.movespeed;
	// 	if (!worldMap[(int)point.pos_X][(int)(point.pos_Y - point.dir_Y * point.movespeed)])
	// 		point.pos_Y -= point.dir_Y * point.movespeed;
	// }
	// if (set->right == 1)
	// {
	// 	olddir_x = point.dir_X;
	// 	point.dir_X = point.dir_X * cos(-point.rotspeed) - point.dir_Y * sin(-point.rotspeed);
	// 	point.dir_Y = olddir_x * sin(-point.rotspeed) + point.dir_Y * cos(-point.rotspeed);
	// 	oldplane_x = point.plane_X;
	// 	point.plane_X = point.plane_X * cos(-point.rotspeed) - point.plane_Y * sin(-point.rotspeed);
	// 	point.plane_Y = oldplane_x * sin(-point.rotspeed) + point.plane_Y * cos(-point.rotspeed);
	// }
	// if (set->left == 1)
	// {
	// 	olddir_x = point.dir_X;
	// 	point.dir_X = point.dir_X * cos(point.rotspeed) - point.dir_Y * sin(point.rotspeed);
	// 	point.dir_Y = olddir_x * sin(point.rotspeed) + point.dir_Y * cos(point.rotspeed);
	// 	oldplane_x = point.plane_X;
	// 	point.plane_X = point.plane_X * cos(point.rotspeed) - point.plane_Y * sin(point.rotspeed);
	// 	point.plane_Y = oldplane_x * sin(point.rotspeed) + point.plane_Y * cos(point.rotspeed);
	// }
	return (0);
}

int		key_release(int keycode, t_set *set)
{
  if (keycode == LEFT_KEY)
    set->left = 0;
  if (keycode == RIGHT_KEY)
    set->right = 0;
  if (keycode == UP_KEY)
    set->up = 0;
  if (keycode == DOWN_KEY)
    set->down = 0;
	if (keycode == M_KEY)
    {
		if (set->map == 0)
			set->map = 1;
		else
			set->map = 0;
	}
  return (0);
}

void	key_action(t_set *set)
{
	double	olddir_x;
	double	oldplane_x;
	
	if (set->up == 1)
	{
		if (!worldMap[(int)(point.pos_X + point.dir_X * point.movespeed)][(int)point.pos_Y])
			point.pos_X += point.dir_X * point.movespeed;
		if (!worldMap[(int)point.pos_X][(int)(point.pos_Y + point.dir_Y * point.movespeed)])
			point.pos_Y += point.dir_Y * point.movespeed;
	}
	if (set->down == 1)
	{
		if (!worldMap[(int)(point.pos_X - point.dir_X * point.movespeed)][(int)point.pos_Y])
			point.pos_X -= point.dir_X * point.movespeed;
		if (!worldMap[(int)point.pos_X][(int)(point.pos_Y - point.dir_Y * point.movespeed)])
			point.pos_Y -= point.dir_Y * point.movespeed;
	}
	if (set->right == 1)
	{
		olddir_x = point.dir_X;
		point.dir_X = point.dir_X * cos(-point.rotspeed) - point.dir_Y * sin(-point.rotspeed);
		point.dir_Y = olddir_x * sin(-point.rotspeed) + point.dir_Y * cos(-point.rotspeed);
		oldplane_x = point.plane_X;
		point.plane_X = point.plane_X * cos(-point.rotspeed) - point.plane_Y * sin(-point.rotspeed);
		point.plane_Y = oldplane_x * sin(-point.rotspeed) + point.plane_Y * cos(-point.rotspeed);
	}
	if (set->left == 1)
	{
		olddir_x = point.dir_X;
		point.dir_X = point.dir_X * cos(point.rotspeed) - point.dir_Y * sin(point.rotspeed);
		point.dir_Y = olddir_x * sin(point.rotspeed) + point.dir_Y * cos(point.rotspeed);
		oldplane_x = point.plane_X;
		point.plane_X = point.plane_X * cos(point.rotspeed) - point.plane_Y * sin(point.rotspeed);
		point.plane_Y = oldplane_x * sin(point.rotspeed) + point.plane_Y * cos(point.rotspeed);
	}
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
	int		line_screenHeight;
	int		draw_start;
	int		draw_end;
	int		color;
	
	x = 0;
	i = 0;
	w = screenWidth;

	for(int y = 0; y < screenHeight; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = p->dir_X - p->plane_X;
		float rayDirY0 = p->dir_Y - p->plane_Y;
		float rayDirX1 = p->dir_X + p->plane_X;
		float rayDirY1 = p->dir_Y + p->plane_Y;

		// Current y position compared to the center of the screen (the horizon)
		int center = y - screenHeight / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / center;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = p->pos_X + rowDistance * rayDirX0;
		float floorY = p->pos_Y + rowDistance * rayDirY0;

		for(int k = 0; k < screenWidth; ++k)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth -1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight -1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 5;

			int color;

			// floor
			color = p->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			set->img.data[y * screenWidth + k] = color;

			color = p->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			set->img.data[(screenHeight - y - 1) * screenWidth + k] = color;
		}
	}

	
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
		
		line_screenHeight = (int)(screenHeight / p->perpwalldist);
		draw_start = -line_screenHeight / 2 + screenHeight / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_screenHeight / 2 + screenHeight / 2;
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

		point.step = 1.0 * texHeight / line_screenHeight; 
		point.texture_pos = (draw_start - screenHeight / 2 + line_screenHeight / 2) * point.step;

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
				color = (color >> 1) & 8355711;
			// color /= 2;
			set->img.data[i * screenWidth + x] = color;
			i++;
		}
		// sprite를 위한 것
		p->zBuffer[x] = p->perpwalldist;
		x++;
	}
}

void    sprite_cast(t_point *p)
{
    for(int i = 0; i < numSprite; i++)
    {
        spriteOrder[i] = i;
        spriteDistance[i] = ((p->pos_X - spr[i].x) *  (p->pos_X - spr[i].x) + (p->pos_Y - spr[i].y) * (p->pos_Y - spr[i].y));
    }
    // 거리가 먼 순으로 sprite를 정렬한다.
    arrange_Sprite();
    // 정렬된 sprite로 screen에 그리기
    for(int i = 0; i < numSprite; i++)
    {
        // 가장 거리가 먼 sprite부터 시작
        double  spriteX = spr[spriteOrder[i]].x - p->pos_X;
        double  spriteY = spr[spriteOrder[i]].y - p->pos_Y;
        //transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]
        double  invDet = 1.0 / (p->plane_X * p->dir_Y - p->dir_X * p->plane_Y);
        double  transformX = invDet * (p->dir_Y * spriteX - p->dir_X * spriteY);
        double  transformY = invDet * (-p->plane_Y * spriteX + p->plane_X * spriteY);
        int spriteScreenX = (int)((screenWidth / 2) * (1 + transformX / transformY));
        // sprite 크기 조절을 해주는 변수
        int     uDiv = 1;
        int     vDiv = 1;
        double  vMove = 0.0;
        int     vMoveScreen = (int)(vMove / transformY);
        // spritescreenHeight, spritescreenWidth 계산
        // 어안렌즈를 방지하기위해 transfromY를 사용
        int     spritescreenHeight = (int)fabs((screenHeight / transformY) / vDiv);
        int     drawStartY = (screenHeight / 2 + vMoveScreen) - spritescreenHeight / 2;
        int     drawEndY = (screenHeight / 2 + vMoveScreen) + spritescreenHeight / 2;
        drawStartY = drawStartY < 0 ? 0 : drawStartY;
        drawEndY = drawEndY >= screenHeight ? screenHeight - 1: drawEndY;
        int     spritescreenWidth = (int)fabs((screenHeight / transformY) / uDiv);
        int     drawStartX = spriteScreenX - spritescreenWidth / 2;
        int     drawEndX = spriteScreenX + spritescreenWidth / 2;
        drawStartX = drawStartX < 0 ? 0 : drawStartX;
        drawEndX = drawEndX >= screenWidth ? screenWidth - 1 : drawEndX;
        // 세로로 sprite를 그려준다.
        for(int x = drawStartX; x < drawEndX; x++)
        {
            int texX = (int)((256 * (x - (-spritescreenWidth / 2 + spriteScreenX)) * texWidth / spritescreenWidth) / 256);
            // sprite를 그릴지 안그릴지 결정한다.
            // 내 시야의 밖에 있거나, 벽에 너머에 있거나를 계산한다.
            int w = screenWidth;
            //if (0 < transformY < (int)ptr->info.zBuffer[x] && 0 < x < w)
            if(transformY > 0 && x > 0 && x < w && transformY < p->zBuffer[x])
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y - vMoveScreen) * 256 - screenHeight * 128 + spritescreenHeight * 128;
                    int texY = ((d * texHeight) / spritescreenHeight) / 256;
                    int color = p->texture[spr[spriteOrder[i]].texnum][texY * texWidth + texX];
                    if ((color & 0x00FFFFFF) != 0)
                        set.img.data[y * screenWidth + x] = color;
                }
            }
        }
    }
}

void	clean_screen(t_set *set)
{
	int		i;

	i = 0;
	while (i <= screenHeight * screenWidth)
		set->img.data[i++] = 0;
}

int		main_loop(t_set *set)
{
	clean_screen(set);
	carl_ray(set, &point);
	sprite_cast(&point);

	if (set->map == 1)
		parse_draw_map(set->img, worldMap, 0xcc82cc);
	//parse_draw_line(set->img, worldMap, 0xffe6c1);
	key_action(set);

	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
	return (0);
}

void	draw_texture()
{
	int i;
	int j;
	
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
}

void	load_file(t_point *point, int num, char *path)
{
	t_img img;
	int x;
	int y;
	

	img.img_ptr = mlx_xpm_file_to_image(set.mlx_ptr, path, &img.img_width, &img.img_height);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

	x = 0;
	y = 0;
	
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			point->texture[num][img.img_width * y + x] = img.data[img.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(set.mlx_ptr, img.img_ptr);
}

void	load_tex(void)
{
	load_file(&point, 0, "img/eagle.xpm");
	load_file(&point, 1, "img/redbrick.xpm");
	load_file(&point, 2, "img/purplestone.xpm");
	load_file(&point, 3, "img/greystone.xpm");
	load_file(&point, 4, "img/bluestone.xpm");
	load_file(&point, 5, "img/mossy.xpm");
	load_file(&point, 6, "img/wood.xpm");
	load_file(&point, 7, "img/colorstone.xpm");
	
	// sprite texture
	load_file(&point, 8, "img/barrel.xpm");
	load_file(&point, 9, "../image02_resize.xpm");
	load_file(&point, 10, "img/greenlight.xpm");
}

int		main(int ac, char *av[])
{
	int	i;
	int	j;

	point.pos_X = 22.0;
	point.pos_Y = 11.5;
	point.dir_X = -1;
	point.dir_Y = 0;
	point.plane_X = 0;
	point.plane_Y = 0.66;
	point.rotspeed = 0.02;
	point.movespeed = 0.1;

	set.up = 0;
	set.left = 0;
	set.right = 0;
	set.down = 0;
	point.hit = 0;

	set.mlx_ptr = mlx_init();

	i = 0;
	j = 0;
	
	make_window(&set);
	load_tex();
	// draw_texture();
	mlx_hook(set.win_ptr, KeyPress, 0, key_press, &set);
	mlx_hook(set.win_ptr, KeyRelease, 0, key_release, &set);
	mlx_loop_hook(set.mlx_ptr, &main_loop, &set);
	mlx_loop(set.mlx_ptr);

	return (0);
}
