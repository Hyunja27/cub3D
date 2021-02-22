/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:53:53 by spark             #+#    #+#             */
/*   Updated: 2021/02/23 01:25:47 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_file(t_set *set, int num, char *path)
{
	t_img	img_tmp;
	int		x;
	int		y;

	img_tmp.img_ptr = mlx_xpm_file_to_image(set->mlx_ptr, path, \
	&img_tmp.img_width, &img_tmp.img_height);
	set->img.img_height = img_tmp.img_height;
	set->img.img_width = img_tmp.img_width;
	img_tmp.data = (int *)mlx_get_data_addr(img_tmp.img_ptr, \
	&img_tmp.bpp, &img_tmp.size_l, &img_tmp.endian);
	x = 0;
	y = 0;
	while (y < img_tmp.img_height)
	{
		x = 0;
		while (x < img_tmp.img_width)
		{
			set->p.texture[num][img_tmp.img_width * y + x] = \
			img_tmp.data[img_tmp.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(set->mlx_ptr, img_tmp.img_ptr);
}

void	load_tex(t_set *set)
{
	load_file(set, 0, set->minfo.so_path);
	load_file(set, 1, set->minfo.no_path);
	load_file(set, 2, set->minfo.ea_path);
	load_file(set, 3, set->minfo.we_path);
	if (set->minfo.f_kind)
		load_file(set, 8, set->minfo.f_path);
	if (set->minfo.c_kind)
		load_file(set, 10, set->minfo.c_path);
	load_file(set, 9, set->minfo.sp_path);
}
