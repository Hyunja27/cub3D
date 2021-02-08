/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/02/08 17:45:37 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
  int *dst;

 // dst = data->data + (y * data->size_l + x * (data->bpp / 8));
  dst = data->data + (y * SCREEN_WIDTH + x );
  *(unsigned int*)dst = color;
}


void	draw_square(t_set *s, int start, int color)
{
	int		i = 0;
	int		j = 0;
	
	while (j < MAP_BOX_SIZE)
	{
		i = 0;
		while (i < MAP_BOX_SIZE)
		{
			s->img.data[start + i] = color;
			i++;
		}
		start += SCREEN_WIDTH;
		j++;
	}
}


void    arrange_Sprite(t_set *s)
{
    int     tmp;
    double  dis_tmp;
    double  max = 0;
    for(int i = 0; i < SPRITE_NUM - 1; i++)
    {
        max = s->spr.spriteDistance[i];
        for(int j = i + 1; j < SPRITE_NUM; j++)
        {
            if (max <= s->spr.spriteDistance[j])
            {
                max = s->spr.spriteDistance[j];
                tmp = s->spr.spriteOrder[i];
                s->spr.spriteOrder[i] = s->spr.spriteOrder[j];
                s->spr.spriteOrder[j] = tmp;
                dis_tmp = s->spr.spriteDistance[i];
                s->spr.spriteDistance[i] = s->spr.spriteDistance[j];
                s->spr.spriteDistance[j] = dis_tmp;
            }
        }
    }
}

int		move(t_set *s)
{
	int i;
	int j;
	int k;
	int map2d_pos_X;
	int map2d_pos_Y;
	// for(int a = 0; a < screenHeight * screenWidth; a++)
	// 	set->img.data[a] = 0;

	map2d_pos_X = s->p.pos_X * MAP_BOX_SIZE;
	map2d_pos_Y = s->p.pos_Y * MAP_BOX_SIZE;
	for (i = (int)map2d_pos_X, k = 4; i < map2d_pos_X + 2; i++, k -= 2)
		{
			for (j = (map2d_pos_Y) + k; j <=  (map2d_pos_Y) + 4; j++)
			my_mlx_pixel_put(&s->img, j, i, 0x0000FF00);
		}
	for (i = map2d_pos_X + 2, k = 0; i < map2d_pos_X + 4; i++, k += 2)
		{
			for (j = (map2d_pos_Y) + k; j <=  (map2d_pos_Y) + 4; j++)
			my_mlx_pixel_put(&s->img, j, i, 0x0000FF00);
		}
	// draw_square(set, point.pos_X, 0x0000FF00);
	
	return (0);
}

// void	draw_cross_line(t_img set, int start, int color)
// {
// 	int		i = 0;

// 	while ((((start + i) % SCREEN_WIDTH) != 0))
// 		set.data[start + i++] = color;
// 	i = 0;
// 	while ((((start - i) % SCREEN_WIDTH) != 0))
// 		set.data[start - i++] = color;
// 	i = 0;
// 	while (((i * SCREEN_WIDTH) <= SCREEN_WIDTH * SCREEN_HEIGHT) && (((start + (i * SCREEN_WIDTH)) % SCREEN_WIDTH) != 0))
// 		set.data[start + (i++ * SCREEN_WIDTH)] = color;
// 	i = 0;
// 	while (((start - (i * SCREEN_WIDTH)) >= 0) && (((start + (i * SCREEN_WIDTH)) % SCREEN_WIDTH) != 0))
// 		set.data[start - (i++ * SCREEN_WIDTH)] = color;
// }

// void	parse_draw_line(t_img set, int worldmap[24][24],int color)
// {
// 	int i;
// 	int j;
// 	int point;

// 	i = 0;
// 	j = 0;
// 	point = 0;
// 	while (i < COLS)
// 	{
// 		while (j < ROWS)
// 		{
// 			if (worldMap[i][j] == 1)
// 			{
// 				point = (i * (SCREEN_WIDTH * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
// 				// if (point > BOX_screenWidth)
// 				// 	draw_cross_line(set, point, color);
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	// draw_strange_line(set, 5000, 0xffffff);
// }

void	parse_draw_map(t_set *s, int world[24][24],int color)
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
			point = (i * (SCREEN_WIDTH * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
			//draw_square(set, point, 0);
			if (world[i][j] != 0)
			{
				point = (i * (SCREEN_WIDTH * MAP_BOX_SIZE)) + (j * MAP_BOX_SIZE);
				draw_square(s, point, color);
			}
			j++;
		}
		j = 0;
		i++;
	}
	move(s);
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

void	key_action(t_set *s)
{
	double	olddir_x;
	double	oldplane_x;
	
	if (s->up == 1)
	{
		if (!worldMap[(int)(s->p.pos_X + s->p.dir_X * s->p.movespeed)][(int)s->p.pos_Y])
			s->p.pos_X += s->p.dir_X * s->p.movespeed;
		if (!worldMap[(int)s->p.pos_X][(int)(s->p.pos_Y + s->p.dir_Y * s->p.movespeed)])
			s->p.pos_Y += s->p.dir_Y * s->p.movespeed;
	}
	if (s->down == 1)
	{
		if (!worldMap[(int)(s->p.pos_X - s->p.dir_X * s->p.movespeed)][(int)s->p.pos_Y])
			s->p.pos_X -= s->p.dir_X * s->p.movespeed;
		if (!worldMap[(int)s->p.pos_X][(int)(s->p.pos_Y - s->p.dir_Y * s->p.movespeed)])
			s->p.pos_Y -= s->p.dir_Y * s->p.movespeed;
	}
	if (s->right == 1)
	{
		olddir_x = s->p.dir_X;
		s->p.dir_X = s->p.dir_X * cos(-s->p.rotspeed) - s->p.dir_Y * sin(-s->p.rotspeed);
		s->p.dir_Y = olddir_x * sin(-s->p.rotspeed) + s->p.dir_Y * cos(-s->p.rotspeed);
		oldplane_x = s->p.plane_X;
		s->p.plane_X = s->p.plane_X * cos(-s->p.rotspeed) - s->p.plane_Y * sin(-s->p.rotspeed);
		s->p.plane_Y = oldplane_x * sin(-s->p.rotspeed) + s->p.plane_Y * cos(-s->p.rotspeed);
	}
	if (s->left == 1)
	{
		olddir_x = s->p.dir_X;
		s->p.dir_X = s->p.dir_X * cos(s->p.rotspeed) - s->p.dir_Y * sin(s->p.rotspeed);
		s->p.dir_Y = olddir_x * sin(s->p.rotspeed) + s->p.dir_Y * cos(s->p.rotspeed);
		oldplane_x = s->p.plane_X;
		s->p.plane_X = s->p.plane_X * cos(s->p.rotspeed) - s->p.plane_Y * sin(s->p.rotspeed);
		s->p.plane_Y = oldplane_x * sin(s->p.rotspeed) + s->p.plane_Y * cos(s->p.rotspeed);
	}
}

void	make_window(t_set *set)
{
	set->win_ptr = mlx_new_window(set->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster Practice");
	set->img.img_ptr = mlx_new_image(set->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	set->img.data = (int*)mlx_get_data_addr(set->img.img_ptr, &set->img.bpp, &set->img.size_l, &set->img.endian);
}

void	carl_ray(t_set *s)
{	
	int		x;
	int		y;
	int		i;
	double	w;
	
	w = SCREEN_WIDTH;
	x = 0;
	y = 0;
	i = 0;
	

	while(y < SCREEN_HEIGHT)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		s->flr.rayDirX0 = s->p.dir_X - s->p.plane_X;
		s->flr.rayDirY0 = s->p.dir_Y - s->p.plane_Y;
		s->flr.rayDirX1 = s->p.dir_X + s->p.plane_X;
		s->flr.rayDirY1 = s->p.dir_Y + s->p.plane_Y;

		// Current y position compared to the center of the screen (the horizon)
		s->flr.center = y - SCREEN_HEIGHT / 2;

		// Vertical position of the camera.
		s->flr.posZ = 0.5 * SCREEN_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		s->flr.rowDistance = s->flr.posZ / s->flr.center;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		s->flr.floorStepX = s->flr.rowDistance * (s->flr.rayDirX1 - s->flr.rayDirX0) / SCREEN_WIDTH;
		s->flr.floorStepY = s->flr.rowDistance * (s->flr.rayDirY1 - s->flr.rayDirY0) / SCREEN_WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		s->flr.floorX = s->p.pos_X + s->flr.rowDistance * s->flr.rayDirX0;
		s->flr.floorY = s->p.pos_Y + s->flr.rowDistance * s->flr.rayDirY0;

		while(i < SCREEN_WIDTH)
		{
			// get the texture coordinate from the fractional part
			s->flr.tx = (int)(TEX_WIDTH * (s->flr.floorX - (int)(s->flr.floorX))) & (TEX_WIDTH -1);
			s->flr.ty = (int)(TEX_HEIGHT * (s->flr.floorY - (int)(s->flr.floorY))) & (TEX_HEIGHT -1);

			s->flr.floorX += s->flr.floorStepX;
			s->flr.floorY += s->flr.floorStepY;

			// choose texture and draw the pixel
			s->tex.floorTexture = 6;
			s->tex.ceilingTexture = 6;
			// floor
			s->tex.color = s->p.texture[s->tex.floorTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
			s->tex.color = (s->tex.color >> 1) & 8355711; // make a bit darker

			s->img.data[y * SCREEN_WIDTH + i] = s->tex.color;

			s->tex.color = s->p.texture[s->tex.ceilingTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
			s->tex.color = (s->tex.color >> 1) & 8355711; // make a bit darker

			s->img.data[(SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + i] = s->tex.color;
			i++;
		}
		y++;
		i = 0;
	}
	
	while (x < (int)w)
	{
		s->p.hit = 0;
		
		s->p.camera_X = 2 * x / w - 1;
		s->p.raydir_X = s->p.dir_X + s->p.plane_X * s->p.camera_X;
		s->p.raydir_Y = s->p.dir_Y + s->p.plane_Y * s->p.camera_X;

		s->p.position_X = (int)s->p.pos_X;
		s->p.position_Y = (int)s->p.pos_Y;
		
		s->p.deltadist_X = fabs(1 / s->p.raydir_X);
		s->p.deltadist_Y = fabs(1 / s->p.raydir_Y);

		if (s->p.raydir_X < 0)
		{
			s->p.step_X = -1;
			s->p.side_X = (s->p.pos_X - s->p.position_X) * s->p.deltadist_X;
		}
		else
		{
			s->p.step_X = 1;
			s->p.side_X = (s->p.position_X + 1.0 - s->p.pos_X) * s->p.deltadist_X;
		}
		if (s->p.raydir_Y < 0)
		{
			s->p.step_Y = -1;
			s->p.side_Y = (s->p.pos_Y - s->p.position_Y) * s->p.deltadist_Y;
		}
		else
		{
			s->p.step_Y = 1;
			s->p.side_Y = (s->p.position_Y + 1.0 - s->p.pos_Y) * s->p.deltadist_Y;
		}
		
		while (s->p.hit == 0)
		{
			if (s->p.side_X < s->p.side_Y)
			{
				s->p.side_X += s->p.deltadist_X;
				s->p.position_X += s->p.step_X;
				s->p.hit_side = 0;
			}
			else
			{
				s->p.side_Y += s->p.deltadist_Y;
				s->p.position_Y += s->p.step_Y;
				s->p.hit_side = 1;
			}
			if (worldMap[s->p.position_X][s->p.position_Y] > 0)
				s->p.hit = 1;
		}

		if (s->p.hit_side == 0)
			s->p.perpwalldist = (s->p.position_X - s->p.pos_X + (1 - s->p.step_X) / 2) / s->p.raydir_X;
		else
			s->p.perpwalldist = (s->p.position_Y - s->p.pos_Y + (1 - s->p.step_Y) / 2) / s->p.raydir_Y;
		
		s->cr.line_screenHeight = (int)(SCREEN_HEIGHT / s->p.perpwalldist);
		s->cr.draw_start = -s->cr.line_screenHeight / 2 + SCREEN_HEIGHT / 2;
		if (s->cr.draw_start < 0)
			s->cr.draw_start = 0;
		s->cr.draw_end = s->cr.line_screenHeight / 2 + SCREEN_HEIGHT / 2;
		if (s->cr.draw_end >= SCREEN_HEIGHT)
			s->cr.draw_end = SCREEN_HEIGHT - 1;
		
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


		// s->tex.texture_kind = worldMap[s->p.position_X][s->p.position_Y] - 1;

		// 0 = 동
		// 1 = 서
		// 2 = 남
		// 3 = 북
	
		if (s->p.hit_side == 1)
		{
			if (s->p.raydir_Y > 0)
				s->tex.texture_kind = 0;
			else
				s->tex.texture_kind = 1;
		}
		else if (s->p.hit_side == 0)
		{
			if (s->p.raydir_X > 0)
				s->tex.texture_kind = 2;
			else
				s->tex.texture_kind = 3;
		}



		s->p.step = 1.0 * TEX_HEIGHT / s->cr.line_screenHeight; 
		s->p.texture_pos = (s->cr.draw_start - SCREEN_HEIGHT / 2 + s->cr.line_screenHeight / 2) * s->p.step;

		if (s->p.hit_side == 0)
			s->cr.wallX = s->p.pos_Y + s->p.perpwalldist * s->p.raydir_Y;
		else
			s->cr.wallX = s->p.pos_X + s->p.perpwalldist * s->p.raydir_X;
		s->cr.wallX -= floor(s->cr.wallX); 
			
		s->tex.texX = (int)(s->cr.wallX * (double)TEX_WIDTH);
		if (s->p.hit_side == 0 && s->p.raydir_X > 0)
			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
		if (s->p.hit_side == 1 && s->p.raydir_X < 0)
			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
		
		i = s->cr.draw_start;
		
		while (i < s->cr.draw_end)
		{	
			s->tex.texY = (int)s->p.texture_pos & (TEX_HEIGHT - 1);
			s->p.texture_pos += s->p.step;
			s->tex.color = s->p.texture[s->tex.texture_kind][TEX_HEIGHT * s->tex.texY + s->tex.texX];
			// if (s->p.hit_side == 1)
			// 	s->tex.color = (s->tex.color >> 1) & 8355711;
			// color /= 2;
			s->img.data[i * SCREEN_WIDTH + x] = s->tex.color;
			i++;
		}
		// sprite를 위한 것
		s->p.zBuffer[x] = s->p.perpwalldist;
		x++;
	}
}

void    sprite_cast(t_set *s)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
    while(i < SPRITE_NUM)
    {
        s->spr.spriteOrder[i] = i;
        s->spr.spriteDistance[i] = ((s->p.pos_X - spr[i].x) *  (s->p.pos_X - spr[i].x) + (s->p.pos_Y - spr[i].y) * (s->p.pos_Y - spr[i].y));
		i++;
	}
	i = 0;
    // 거리가 먼 순으로 sprite를 정렬한다.
    arrange_Sprite(s);
    // 정렬된 sprite로 screen에 그리기
    while(i < SPRITE_NUM)
    {
        // 가장 거리가 먼 sprite부터 시작
        s->spr.spriteX = spr[s->spr.spriteOrder[i]].x - s->p.pos_X;
        s->spr.spriteY = spr[s->spr.spriteOrder[i]].y - s->p.pos_Y;
        //transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]
        s->spr.invDet = 1.0 / (s->p.plane_X * s->p.dir_Y - s->p.dir_X * s->p.plane_Y);
        s->spr.transformX = s->spr.invDet * (s->p.dir_Y * s->spr.spriteX - s->p.dir_X * s->spr.spriteY);
        s->spr.transformY = s->spr.invDet * (-s->p.plane_Y * s->spr.spriteX + s->p.plane_X * s->spr.spriteY);
        s->spr.spriteScreenX = (int)((SCREEN_WIDTH / 2) * (1 + s->spr.transformX / s->spr.transformY));
        // sprite 크기 조절을 해주는 변수
        s->spr.uDiv = 1;
        s->spr.vDiv = 1;
        s->spr.vMove = 0.0;
        s->spr.vMoveScreen = (int)(s->spr.vMove / s->spr.transformY);
        // spritescreenHeight, spritescreenWidth 계산
        // 어안렌즈를 방지하기위해 transfromY를 사용
        s->spr.spritescreenHeight = (int)fabs((SCREEN_HEIGHT / s->spr.transformY) / s->spr.vDiv);
        s->spr.drawStartY = (SCREEN_HEIGHT / 2 + s->spr.vMoveScreen) - s->spr.spritescreenHeight / 2;
        s->spr.drawEndY = (SCREEN_HEIGHT / 2 + s->spr.vMoveScreen) + s->spr.spritescreenHeight / 2;
        s->spr.drawStartY = s->spr.drawStartY < 0 ? 0 : s->spr.drawStartY;
        s->spr.drawEndY = s->spr.drawEndY >= SCREEN_HEIGHT ? SCREEN_HEIGHT - 1: s->spr.drawEndY;
		
        s->spr.spritescreenWidth = (int)fabs((SCREEN_HEIGHT / s->spr.transformY) / s->spr.uDiv);
        s->spr.drawStartX = s->spr.spriteScreenX - s->spr.spritescreenWidth / 2;
        s->spr.drawEndX = s->spr.spriteScreenX + s->spr.spritescreenWidth / 2;

		s->spr.drawStartX = s->spr.drawStartX < 0 ? 0 : s->spr.drawStartX;
        s->spr.drawEndX = s->spr.drawEndX >= SCREEN_WIDTH ? SCREEN_WIDTH - 1 : s->spr.drawEndX;
        // 세로로 sprite를 그려준다.
        x = s->spr.drawStartX;
		while(x < s->spr.drawEndX)
        {
	
	
            s->spr.texX = (int)((256 * (x - (-s->spr.spritescreenWidth / 2 + s->spr.spriteScreenX)) * TEX_WIDTH / s->spr.spritescreenWidth) / 256);
            // sprite를 그릴지 안그릴지 결정한다.
            // 내 시야의 밖에 있거나, 벽에 너머에 있거나를 계산한다.
            int w = SCREEN_WIDTH;
            //if (0 < transformY < (int)ptr->info.zBuffer[x] && 0 < x < w)
            if(s->spr.transformY > 0 && x > 0 && x < w && s->spr.transformY < s->p.zBuffer[x])
            {
				y = s->spr.drawStartY;
                while (y < s->spr.drawEndY)
                {
                    s->spr.d = (y - s->spr.vMoveScreen) * 256 - SCREEN_HEIGHT * 128 + s->spr.spritescreenHeight * 128;
                    s->spr.texY = ((s->spr.d * TEX_HEIGHT) / s->spr.spritescreenHeight) / 256;
                    s->spr.spr_color = s->p.texture[spr[s->spr.spriteOrder[i]].texnum][s->spr.texY * TEX_WIDTH + s->spr.texX];
                    if ((s->spr.spr_color & 0x00FFFFFF) != 0)
                        s->img.data[y * SCREEN_WIDTH + x] = s->spr.spr_color;
					y++;
				}
            }
			x++;
        }
		i++;
    }
}

void	clean_screen(t_set *set)
{
	int		i;

	i = 0;
	while (i <= SCREEN_HEIGHT * SCREEN_WIDTH)
		set->img.data[i++] = 0;
}

int		main_loop(t_set *set)
{
	clean_screen(set);
	carl_ray(set);
	//sprite_cast(set);

	if (set->map == 1)
		parse_draw_map(set, worldMap, 0xcc82cc);
	key_action(set);

	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
	return (0);
}

void	load_file(t_set *set, int num, char *path)
{
	t_img img_tmp;
	int x;
	int y;

	img_tmp.img_ptr = mlx_xpm_file_to_image(set->mlx_ptr, path, &img_tmp.img_width, &img_tmp.img_height);
	img_tmp.data = (int *)mlx_get_data_addr(img_tmp.img_ptr, &img_tmp.bpp, &img_tmp.size_l, &img_tmp.endian);
	
	x = 0;
	y = 0;
	
	while (y < img_tmp.img_height)
	{
		x = 0;
		while (x < img_tmp.img_width)
		{
			set->p.texture[num][img_tmp.img_width * y + x] = img_tmp.data[img_tmp.img_width * y + x];
			x++;
		}
		y++;
	}
	printf("%s\n", path);
	mlx_destroy_image(set->mlx_ptr, img_tmp.img_ptr);
}

void	load_tex(t_set *set)
{
	load_file(set, 0, "img/wall_e.xpm");
	load_file(set, 1, "img/wall_w.xpm");
	load_file(set, 2, "img/wall_s.xpm");
	load_file(set, 3, "img/wall_n.xpm");
	load_file(set, 4, "img/bluestone.xpm");
	load_file(set, 5, "img/mossy.xpm");
	load_file(set, 6, "img/wood.xpm");
	load_file(set, 7, "img/colorstone.xpm");
	
	// sprite texture
	load_file(set, 8, "img/barrel.xpm");
	load_file(set, 9, "img/image02_resize.xpm");
	load_file(set, 10, "img/greenlight.xpm");
}

// 										&&&&&&&&&&&&&&&&&&&&&&
// 										&&&&&&&&&&&&&&&&&&&&&&
// 										&&&&&&&&&&&&&&&&&&&&&&
// 						&&&&&&&& map_parsing 로직 만드눈쥴 &&&&&&&&&&&&&
// 										&&&&&&&&&&&&&&&&&&&&&&
// 										&&&&&&&&&&&&&&&&&&&&&&
// 										&&&&&&&&&&&&&&&&&&&&&&

// int		check_str(char *tg, char *src, int len)
// {
// 	int i;

// 	i = -1;
// 	while (--i < len)
// 	{
// 		if (tg[i] != src[i])
// 			return (0);
// 	}
// 	return (1);
// }

// void	get_resol(t_set *s, int fd, char **line)
// {
	
// }

// void	get_text(t_set *s, int fd, char **line)
// {
	
// }

// void	get_corl(t_set *s, int fd, char **line)
// {
	
// }

// void	parse_map(t_set *s)
// {
// 	char*	line;
// 	int		fd;

// 	fd = open ("test_map.cub", O_RDONLY);
// 	is_map(s, fd, &line);
// 	get_resol(s, fd, &line);
// 	get_text(s, fd, &line);
// 	get_corl(s, fd, &line);
// }

int		main(void)
{
	int		i;
	int		j;
	t_set	set;

	set.p.pos_X = 22.0;
	set.p.pos_Y = 11.5;
	set.p.dir_X = -1;
	set.p.dir_Y = 0;
	set.p.plane_X = 0;
	set.p.plane_Y = 0.66;
	set.p.rotspeed = 0.02;
	set.p.movespeed = 0.1;

	set.up = 0;
	set.left = 0;
	set.right = 0;
	set.down = 0;
	set.p.hit = 0;

	set.mlx_ptr = mlx_init();

	i = 0;
	j = 0;
	
	// parse_map(set);
	make_window(&set);
	load_tex(&set);
	mlx_hook(set.win_ptr, KeyPress, 0, key_press, &set);
	mlx_hook(set.win_ptr, KeyRelease, 0, key_release, &set);
	mlx_loop_hook(set.mlx_ptr, &main_loop, &set);
	mlx_loop(set.mlx_ptr);


		// printf("*\n");



	return (0);
}
