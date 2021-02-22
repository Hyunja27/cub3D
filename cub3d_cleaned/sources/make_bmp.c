/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:28:38 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 21:44:27 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_bmp_info(t_bmp *m, t_set *s)
{
	m->bfType1 = 'B';
	m->bfType2 = 'M';
	m->bfSize = (4 * (s->minfo.s_width * s->minfo.s_height)) + 54;
	m->bfReserved1 = 0;
	m->bfReserved2 = 0;
	m->bfOffBits = 54;
	m->biSize = 40;
	m->biWidth = s->minfo.s_width;
	m->biHeight = -s->minfo.s_height;
	m->biPlanes = 1;
	m->biBitCount = 32;
	m->biCompression = 0;
	m->biSizeImage = (4 * (s->minfo.s_width * s->minfo.s_height));
	m->biXPelsPerMeter = s->minfo.s_width;
	m->biYPelsPerMeter = s->minfo.s_height;
	m->biClrUsed = 0;
	m->biClrImportant = 0;
}

t_bmp	make_bmp(t_set *s)
{
	t_bmp	m;
	int		fd;

	fd = open("cub3d_save.bmp", O_RDWR | O_TRUNC | O_CREAT, 0666);
	put_bmp_info(&m, s);
	write(fd, &m, 54);
	write(fd, s->img.data, m.biSizeImage);
	close(fd);
	return (m);
}
