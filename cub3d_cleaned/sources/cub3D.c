/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:37:31 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 23:59:36 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void carl_ray(t_set *s)
{
	int x;
	int y;
	int i;
	double w;

	w = s->minfo.s_width;
	x = 0;
	y = 0;
	i = 0;

	while (y < s->minfo.s_height)
	{
		s->flr.rayDirX0 = s->p.dirX - s->p.planeX;
		s->flr.rayDirY0 = s->p.dirY - s->p.planeY;
		s->flr.rayDirX1 = s->p.dirX + s->p.planeX;
		s->flr.rayDirY1 = s->p.dirY + s->p.planeY;
		s->flr.center = y - s->minfo.s_height / 2;
		s->flr.posZ = 0.5 * s->minfo.s_height;
		s->flr.rowDistance = s->flr.posZ / s->flr.center;
		s->flr.floorStepX = s->flr.rowDistance * (s->flr.rayDirX1 - s->flr.rayDirX0) / s->minfo.s_width;
		s->flr.floorStepY = s->flr.rowDistance * (s->flr.rayDirY1 - s->flr.rayDirY0) / s->minfo.s_width;
		s->flr.floorX = s->p.posX + s->flr.rowDistance * s->flr.rayDirX0;
		s->flr.floorY = s->p.posY + s->flr.rowDistance * s->flr.rayDirY0;

		while (i < s->minfo.s_width)
		{
			s->flr.tx = (int)(TEX_WIDTH * (s->flr.floorX - (int)(s->flr.floorX))) & (TEX_WIDTH - 1);
			s->flr.ty = (int)(TEX_HEIGHT * (s->flr.floorY - (int)(s->flr.floorY))) & (TEX_HEIGHT - 1);
			s->flr.floorX += s->flr.floorStepX;
			s->flr.floorY += s->flr.floorStepY;
			if (s->minfo.f_kind)
			{
				s->tex.floorTexture = 8;
				s->tex.color = s->p.texture[s->tex.floorTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
				s->tex.color = (s->tex.color >> 1) & 8355711;
			}
			else
				s->tex.color = s->minfo.floor;

			s->img.data[y * s->minfo.s_width + i] = s->tex.color;

			if (s->minfo.c_kind)
			{
				s->tex.ceilingTexture = 10;
				s->tex.color = s->p.texture[s->tex.ceilingTexture][TEX_WIDTH * s->flr.ty + s->flr.tx];
				s->tex.color = (s->tex.color >> 1) & 8355711;
			}
			else
				s->tex.color = s->minfo.ceiling;

			s->img.data[(s->minfo.s_height - y - 1) * s->minfo.s_width + i] = s->tex.color;
			i++;
		}
		y++;
		i = 0;
	}

	while (x < (int)w)
	{
		s->p.hit = 0;

		s->p.cameraX = 2 * x / w - 1;
		s->p.raydirX = s->p.dirX + s->p.planeX * s->p.cameraX;
		s->p.raydirY = s->p.dirY + s->p.planeY * s->p.cameraX;

		s->p.positionX = (int)s->p.posX;
		s->p.positionY = (int)s->p.posY;

		s->p.deltadistX = fabs(1 / s->p.raydirX);
		s->p.deltadistY = fabs(1 / s->p.raydirY);

		if (s->p.raydirX < 0)
		{
			s->p.stepX = -1;
			s->p.sideX = (s->p.posX - s->p.positionX) * s->p.deltadistX;
		}
		else
		{
			s->p.stepX = 1;
			s->p.sideX = (s->p.positionX + 1.0 - s->p.posX) * s->p.deltadistX;
		}
		if (s->p.raydirY < 0)
		{
			s->p.stepY = -1;
			s->p.sideY = (s->p.posY - s->p.positionY) * s->p.deltadistY;
		}
		else
		{
			s->p.stepY = 1;
			s->p.sideY = (s->p.positionY + 1.0 - s->p.posY) * s->p.deltadistY;
		}

		while (s->p.hit == 0)
		{
			if (s->p.sideX < s->p.sideY)
			{
				s->p.sideX += s->p.deltadistX;
				s->p.positionX += s->p.stepX;
				s->p.hit_side = 0;
			}
			else
			{
				s->p.sideY += s->p.deltadistY;
				s->p.positionY += s->p.stepY;
				s->p.hit_side = 1;
			}
			if (s->map2[s->p.positionX][s->p.positionY] == 1)
				s->p.hit = 1;
		}

		if (s->p.hit_side == 0)
			s->p.perpwalldist = (s->p.positionX - s->p.posX + (1 - s->p.stepX) / 2) / s->p.raydirX;
		else
			s->p.perpwalldist = (s->p.positionY - s->p.posY + (1 - s->p.stepY) / 2) / s->p.raydirY;

		s->cr.line_screenHeight = (int)(s->minfo.s_height / s->p.perpwalldist);
		s->cr.draw_start = -s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
		if (s->cr.draw_start < 0)
			s->cr.draw_start = 0;
		s->cr.draw_end = s->cr.line_screenHeight / 2 + s->minfo.s_height / 2;
		if (s->cr.draw_end >= s->minfo.s_height)
			s->cr.draw_end = s->minfo.s_height - 1;
		if (s->p.hit_side == 0)
			s->cr.wallX = s->p.posY + s->p.perpwalldist * s->p.raydirY;
		else
			s->cr.wallX = s->p.posX + s->p.perpwalldist * s->p.raydirX;
		s->cr.wallX -= floor(s->cr.wallX);

		s->tex.texX = (int)(s->cr.wallX * (double)TEX_WIDTH);
		if (s->p.hit_side == 0 && s->p.raydirX > 0)
			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;
		if (s->p.hit_side == 1 && s->p.raydirY < 0)
			s->tex.texX = TEX_WIDTH - s->tex.texX - 1;

		s->p.step = 1.0 * TEX_HEIGHT / s->cr.line_screenHeight;
		s->p.texture_pos = (s->cr.draw_start - s->minfo.s_height / 2 + s->cr.line_screenHeight / 2) * s->p.step;

		if (s->p.hit_side == 1)
		{
			if (s->p.raydirY > 0)
				s->tex.texture_kind = 2;
			else
				s->tex.texture_kind = 3;
		}
		else if (s->p.hit_side == 0)
		{
			if (s->p.raydirX > 0)
				s->tex.texture_kind = 0;
			else
				s->tex.texture_kind = 1;
		}

		i = s->cr.draw_start;
		while (i < s->cr.draw_end)
		{
			s->tex.texY = (int)s->p.texture_pos & (TEX_HEIGHT - 1);
			s->p.texture_pos += s->p.step;
			s->tex.color = s->p.texture[s->tex.texture_kind][TEX_HEIGHT * s->tex.texY + s->tex.texX];
			s->img.data[i * s->minfo.s_width + x] = s->tex.color;
			i++;
		}
		s->p.zBuffer[x] = s->p.perpwalldist;
		x++;
	}
}

// void sprite_cast(t_set *s)
// {
// 	int i;
// 	int x;
// 	int y;

// 	i = 0;
// 	x = 0;
// 	y = 0;
// 	s->spr.spriteOrder = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
// 	s->spr.spriteDistance = (int *)malloc(sizeof(int) * s->minfo.num_sprite);
// 	while (i < s->minfo.num_sprite)
// 	{
// 		s->spr.spriteOrder[i] = i;
// 		s->spr.spriteDistance[i] = ((s->p.posX - s->spr.sprt[i].x) * (s->p.posX - s->spr.sprt[i].x) + (s->p.posY - s->spr.sprt[i].y) * (s->p.posY - s->spr.sprt[i].y));
// 		i++;
// 	}
// 	i = 0;
// 	arrange_sprite(s);
// 	while (i < s->minfo.num_sprite)
// 	{
// 		s->spr.spriteX = s->spr.sprt[s->spr.spriteOrder[i]].x - s->p.posX;
// 		s->spr.spriteY = s->spr.sprt[s->spr.spriteOrder[i]].y - s->p.posY;
// 		s->spr.invDet = 1.0 / (s->p.planeX * s->p.dirY - s->p.dirX * s->p.planeY);
// 		s->spr.transformX = s->spr.invDet * (s->p.dirY * s->spr.spriteX - s->p.dirX * s->spr.spriteY);
// 		s->spr.transformY = s->spr.invDet * (-s->p.planeY * s->spr.spriteX + s->p.planeX * s->spr.spriteY);
// 		s->spr.spriteScreenX = (int)((s->minfo.s_width / 2) * (1 + s->spr.transformX / s->spr.transformY));
// 		s->spr.uDiv = 1;
// 		s->spr.vDiv = 1;
// 		s->spr.vMove = 0.0;
// 		s->spr.vMoveScreen = (int)(s->spr.vMove / s->spr.transformY);
// 		s->spr.spritescreenHeight = (int)fabs((s->minfo.s_height / s->spr.transformY) / s->spr.vDiv);
// 		s->spr.drawStartY = (s->minfo.s_height / 2 + s->spr.vMoveScreen) - s->spr.spritescreenHeight / 2;
// 		s->spr.drawEndY = (s->minfo.s_height / 2 + s->spr.vMoveScreen) + s->spr.spritescreenHeight / 2;
// 		s->spr.drawStartY = s->spr.drawStartY < 0 ? 0 : s->spr.drawStartY;
// 		s->spr.drawEndY = s->spr.drawEndY >= s->minfo.s_height ? s->minfo.s_height - 1 : s->spr.drawEndY;

// 		s->spr.spritescreenWidth = (int)fabs((s->minfo.s_height / s->spr.transformY) / s->spr.uDiv);
// 		s->spr.drawStartX = s->spr.spriteScreenX - s->spr.spritescreenWidth / 2;
// 		s->spr.drawEndX = s->spr.spriteScreenX + s->spr.spritescreenWidth / 2;

// 		s->spr.drawStartX = s->spr.drawStartX < 0 ? 0 : s->spr.drawStartX;
// 		s->spr.drawEndX = s->spr.drawEndX >= s->minfo.s_width ? s->minfo.s_width - 1 : s->spr.drawEndX;
// 		x = s->spr.drawStartX;
// 		while (x < s->spr.drawEndX)
// 		{
// 			s->spr.texX = (int)((256 * (x - (-s->spr.spritescreenWidth / 2 + s->spr.spriteScreenX)) * TEX_WIDTH / s->spr.spritescreenWidth) / 256);
// 			int w = s->minfo.s_width;
// 			if (s->spr.transformY > 0 && x > 0 && x < w && s->spr.transformY < s->p.zBuffer[x])
// 			{
// 				y = s->spr.drawStartY;
// 				while (y < s->spr.drawEndY)
// 				{
// 					s->spr.d = (y - s->spr.vMoveScreen) * 256 - s->minfo.s_height * 128 + s->spr.spritescreenHeight * 128;
// 					s->spr.texY = ((s->spr.d * TEX_HEIGHT) / s->spr.spritescreenHeight) / 256;
// 					s->spr.spr_color = s->p.texture[9][s->spr.texY * TEX_WIDTH + s->spr.texX];
// 					if ((s->spr.spr_color & 0x00FFFFFF) != 0)
// 						s->img.data[y * s->minfo.s_width + x] = s->spr.spr_color;
// 					y++;
// 				}
// 			}
// 			x++;
// 		}
// 		i++;
// 	}
// }

// int main_loop(t_set *set)
// {
// 	clean_screen(set);
// 	carl_ray(set);
// 	sprite_cast(set);
// 	if (set->map1 == 1)
// 		parse_draw_map(set);
// 	key_action(set);
// 	mlx_put_image_to_window(set->mlx_ptr, set->win_ptr, set->img.img_ptr, 0, 0);
// 	if (set->save_flag)
// 	{
// 		make_bmp(set);
// 		mlx_destroy_image(set->mlx_ptr, set->img.img_ptr);
// 		mlx_destroy_window(set->mlx_ptr, set->win_ptr);
// 		exit(0);
// 	}
// 	return (0);
// }

// void load_file(t_set *set, int num, char *path)
// {
// 	t_img img_tmp;
// 	int x;
// 	int y;
// 	img_tmp.img_ptr = mlx_xpm_file_to_image(set->mlx_ptr, path, &img_tmp.img_width, &img_tmp.img_height);
// 	img_tmp.data = (int *)mlx_get_data_addr(img_tmp.img_ptr, &img_tmp.bpp, &img_tmp.size_l, &img_tmp.endian);

// 	x = 0;
// 	y = 0;

// 	while (y < img_tmp.img_height)
// 	{
// 		x = 0;
// 		while (x < img_tmp.img_width)
// 		{
// 			set->p.texture[num][img_tmp.img_width * y + x] = img_tmp.data[img_tmp.img_width * y + x];
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_destroy_image(set->mlx_ptr, img_tmp.img_ptr);
// }

// // 0 = 동
// // 1 = 서
// // 2 = 남
// // 3 = 북

// void load_tex(t_set *set)
// {
// 	load_file(set, 0, set->minfo.so_path);
// 	load_file(set, 1, set->minfo.no_path);
// 	load_file(set, 2, set->minfo.ea_path);
// 	load_file(set, 3, set->minfo.we_path);
// 	load_file(set, 4, "img/bluestone.xpm");
// 	load_file(set, 5, "img/mossy.xpm");
// 	load_file(set, 6, "img/wood.xpm");
// 	load_file(set, 7, "img/colorstone.xpm");
// 	if (set->minfo.f_kind)
// 		load_file(set, 8, set->minfo.f_path);
// 	if (set->minfo.c_kind)
// 		load_file(set, 10, set->minfo.c_path);
// 	load_file(set, 9, set->minfo.sp_path);
// }

// void set_pos(t_set *set, char pos)
// {
// 	if (pos == 'E')
// 	{
// 		set->p.dirX = 0;
// 		set->p.dirY = 1;
// 		set->p.planeX = 0.66;
// 		set->p.planeY = 0;
// 	}
// 	if (pos == 'W')
// 	{
// 		set->p.dirX = 0;
// 		set->p.dirY = -1;
// 		set->p.planeX = -0.66;
// 		set->p.planeY = 0;
// 	}
// 	if (pos == 'S')
// 	{
// 		set->p.dirX = 1;
// 		set->p.dirY = 0;
// 		set->p.planeX = 0;
// 		set->p.planeY = -0.66;
// 	}
// 	if (pos == 'N')
// 	{
// 		set->p.dirX = -1;
// 		set->p.dirY = 0;
// 		set->p.planeX = 0;
// 		set->p.planeY = 0.66;
// 	}
// }

// void change_map(t_set *set, int **map, char *temp_map, int i)
// {
// 	int j;

// 	j = -1;
// 	while (++j < set->minfo.m_width)
// 		(*map)[j] = -1;
// 	j = -1;
// 	while (temp_map[++j] != 0)
// 	{
// 		if (temp_map[j] == 'E' || temp_map[j] == 'W' || temp_map[j] == 'S' || temp_map[j] == 'N')
// 		{
// 			set_pos(set, temp_map[j]);
// 			set->p.posX = i;
// 			set->p.posY = j;
// 			temp_map[j] = '0';
// 		}
// 		(*map)[j] = temp_map[j] == ' ' ? -1 : temp_map[j] - '0';
// 		if ((*map)[j] == 2)
// 			set->minfo.num_sprite++;
// 	}
// }

// void get_map_size(t_set *set, int fd, int fd_2, char **line)
// {
// 	int temp_size;

// 	set->minfo.m_height = 0;
// 	set->minfo.m_width = 0;
	
// 	temp_size = ft_strlen(*line);
// 	if (set->minfo.m_width < temp_size)
// 		set->minfo.m_width = temp_size;
// 	set->minfo.m_height++;
// 	write(fd_2, *line, temp_size);
// 	write(fd_2, "\n", 1);
// 	free(*line);
// 	while ((get_next_line(fd, line)) > 0)
// 	{
// 		temp_size = ft_strlen(*line);
// 		if (set->minfo.m_width < temp_size)
// 			set->minfo.m_width = temp_size;
// 		set->minfo.m_height++;
// 		write(fd_2, *line, temp_size);
// 		write(fd_2, "\n", 1);
// 		free(*line);
// 	}
// 	free(*line);
// }

// int get_map(int fd, char **line, t_set *set)
// {
// 	int i;
// 	int fd_2;
// 	char *temp_map;

// 	i = -1;
// 	fd_2 = open("tmp_map", O_CREAT | O_RDWR, 0777);
// 	get_map_size(set, fd, fd_2, line);
// 	set->minfo.num_sprite = 0;
// 	set->map2 = (int **)malloc(sizeof(int *) * set->minfo.m_height);
// 	while (++i < set->minfo.m_height)
// 		set->map2[i] = (int *)malloc(sizeof(int) * set->minfo.m_width);
// 	close(fd);
// 	close(fd_2);
// 	fd_2 = open("tmp_map", O_RDONLY);
// 	i = 0;
// 	while ((get_next_line(fd_2, &temp_map) > 0))
// 	{
// 		change_map(set, &(set->map2[i]), temp_map, i);
// 		i++;
// 		free(temp_map);
// 	}
// 	free(temp_map);
// 	close(fd_2);
// 	set->spr.sprt = (t_sprite *)malloc(sizeof(t_sprite) * set->minfo.num_sprite);
// 	return (1);
// }

// map 유효성 검사
// void init_ck_map(t_set *set, int ***ck_map)
// {
// 	int i;
// 	int j;
// 	int a;

// 	i = 0;
// 	a = 0;
// 	while (i < (set->minfo.m_height + 2))
// 	{
// 		j = 0;
// 		while (j < (set->minfo.m_width + 2))
// 		{
// 			if (i == 0 || j == 0 || i == set->minfo.m_height + 1 || j == set->minfo.m_width + 1)
// 			{
// 				(*ck_map)[i][j] = -1;
// 			}
// 			else
// 			{
// 				if (set->map2[i - 1][j - 1] == 2)
// 				{
// 					set->spr.sprt[a].x = i - 1;
// 					set->spr.sprt[a].y = j - 1;
// 					a++;
// 				}
// 				(*ck_map)[i][j] = set->map2[i - 1][j - 1];
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int is_road(t_set *set, int ***ck_map, int x, int y)
// {
// 	int dir_x[4];
// 	int dir_y[4];
// 	int i;

// 	dir_x[0] = -1;
// 	dir_x[1] = 0;
// 	dir_x[2] = 1;
// 	dir_x[3] = 0;
// 	i = -1;
// 	while (++i < 4)
// 		dir_y[3 - i] = dir_x[i];
// 	i = -1;
// 	if ((*ck_map)[x][y] == 1 || (*ck_map)[x][y] == -2)
// 		return (1);
// 	if ((*ck_map)[x][y] == -1)
// 		return (0);
// 	(*ck_map)[x][y] = -2;
// 	i = -1;
// 	while (++i < 4)
// 		if (!is_road(set, ck_map, x + dir_x[i], y + dir_y[i]))
// 			return (0);
// 	return (1);
// }

// int is_map(t_set *set, int **ck_map)
// {
// 	int is_zero;
// 	int i;
// 	int j;

// 	is_zero = 0;
// 	i = -1;
// 	while (++i < set->minfo.m_height)
// 	{
// 		j = -1;
// 		while (++j < set->minfo.m_width)
// 		{
// 			if (ck_map[i][j] == 0)
// 			{
// 				is_zero = 1;
// 				if (is_road(set, &ck_map, i, j) == 0)
// 					return (0);
// 			}
// 		}
// 	}
// 	if (!is_zero)
// 		return (0);
// 	else
// 		return (1);
// }

// int check_map(t_set *set)
// {
// 	int **ck_map;
// 	int i;
// 	int rt;

// 	ck_map = (int **)malloc(sizeof(int *) * (set->minfo.m_height + 2));
// 	i = -1;
// 	while (++i < set->minfo.m_height + 2)
// 		ck_map[i] = (int *)malloc(sizeof(int) * (set->minfo.m_width + 2));
// 	init_ck_map(set, &ck_map);
// 	rt = is_map(set, ck_map);
// 	i = 0;
// 	while (i < set->minfo.m_height + 2)
// 		free(ck_map[i++]);
// 	free(ck_map);
// 	return (rt);
// }

// int		get_color(char *line)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = ft_atoi(line);
// 	while (*line != ',' && *line)
// 	{
// 		line++;
// 		if (!(*line))
// 			return (-1);
// 	}
// 	g = ft_atoi(++line);
// 	while (*line != ',' && *line)
// 	{
// 		line++;
// 		if (!(*line))
// 			return (0);
// 	}
// 	b = ft_atoi(++line);
// 	return ((r * 256 * 256) + (g * 256) + b);
// }

// int		flag_check(int start, int kind, unsigned char *flag, char *line)
// {
// 	if (((*flag) >> kind & 1) ==  1)
// 		return (-1);
// 	while (line[start] == ' ' || line[start] == '	')
// 		start++;
// 	(*flag) |= 1 << kind;
// 	return (start);
// }

// int		get_fc(t_set *set, int kind, char *line)
// {
// 	int	temp;

// 	if (ft_isdigit(*line))
// 	{
// 		(kind == FL_TEXT_NUM) ? (set->minfo.f_kind = 0) : (set->minfo.c_kind = 0);
// 		(kind == FL_TEXT_NUM) ? (set->minfo.floor = get_color(line)) : (set->minfo.ceiling = get_color(line));
// 		temp = (kind == FL_TEXT_NUM) ? set->minfo.floor : set->minfo.ceiling;
// 		if (temp < 0)
// 			return (0);
// 	}
// 	else if (*line == '.')
// 	{
// 		(kind == FL_TEXT_NUM) ? (set->minfo.f_kind = 1) : (set->minfo.c_kind = 1);
// 		(kind == FL_TEXT_NUM) ? (set->minfo.f_path = ft_strdup(line)) : (set->minfo.c_path = ft_strdup(line));
// 	}
// 	return (1);
// }

// int		error_msg(char *kind)
// {
// 	printf("Error\n %s 중복 입력\n", kind);
// 	return (0);
// }

// void	map_parse(t_set *set, char *map_name)
// {
// 	char			*line;
// 	int				fd = open(map_name, O_RDONLY);
// 	unsigned char	flag;
// 	int				i;
// 	int				rt;

// 	flag = 0;
// 	while (flag != 255 && (rt = get_next_line(fd, &line)) > 0)
// 	{
// 		if (ft_strnstr(line, "EA ", 3))
// 		{
// 			i = flag_check(3, EA_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("EA")) : 0;
// 			set->minfo.ea_path = ft_strdup(line + i);
// 		}
// 		if (ft_strnstr(line, "WE ", 3))
// 		{
// 			i = flag_check(3, WE_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("WE")) : 0;
// 			set->minfo.we_path = ft_strdup(line + i);
// 		}
// 		if (ft_strnstr(line, "SO ", 3))
// 		{
// 			i = flag_check(3, SO_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("SO")) : 0;
// 			set->minfo.so_path = ft_strdup(line + i);
// 		}
// 		if (ft_strnstr(line, "NO ", 3))
// 		{
// 			i = flag_check(3, NO_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("NO")) : 0;
// 			set->minfo.no_path = ft_strdup(line + i);
// 		}
// 		if (ft_strnstr(line, "F ", 2))
// 		{
// 			i = flag_check(2, FL_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("FL")) : 0;
// 			get_fc(set, FL_TEXT_NUM, line + i);
// 		}
// 		if (ft_strnstr(line, "C ", 2))
// 		{
// 			i = flag_check(2, CE_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("CE")) : 0;
// 			get_fc(set, CE_TEXT_NUM, line + i);
// 		}
// 		if (ft_strnstr(line, "S ", 2))
// 		{
// 			i = flag_check(2, SP_TEXT_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("SP")) : 0;
// 			set->minfo.sp_path = ft_strdup(line + i);
// 		}
// 		if (ft_strnstr(line, "R ", 2))
// 		{
// 			i = flag_check(2, RE_NUM, &flag, line);
// 			i < 0 ? exit(error_msg("R")) : 0;
// 			if ((set->minfo.s_width = ft_atoi(line + i)) < 0)
// 				return ;
// 			i += ft_ilencal(set->minfo.s_width);
// 			if ((set->minfo.s_height = ft_atoi(line + i)) < 0)
// 				return ;
// 		}
// 	}
// 	if (rt <= 0)
// 		return ;
// 	while (line[0] != ' ' && !ft_isdigit(line[0]))
// 		get_next_line(fd, &line);
// 	get_map(fd, &line, set);
// 	if (!check_map(set))
// 		printf("Map Error\n");
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
