/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 21:28:38 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:13:36 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_bmp_info(t_bmp *m, t_set *s)
{
	m->bftype1 = 'B';
	m->bftype2 = 'M';
	m->bfsize = (4 * (s->minfo.s_width * s->minfo.s_height)) + 54;
	m->bfreserved1 = 0;
	m->bfreserved2 = 0;
	m->bfoffbits = 54;
	m->bisize = 40;
	m->biwidth = s->minfo.s_width;
	m->biheight = -s->minfo.s_height;
	m->biplanes = 1;
	m->bibitcount = 32;
	m->bicompression = 0;
	m->bisizeimage = (4 * (s->minfo.s_width * s->minfo.s_height));
	m->bixpelspermeter = s->minfo.s_width;
	m->biypelspermeter = s->minfo.s_height;
	m->biclrused = 0;
}

t_bmp	make_bmp(t_set *s)
{
	t_bmp	m;
	int		fd;

	fd = open("cub3d_save.bmp", O_RDWR | O_TRUNC | O_CREAT, 0666);
	put_bmp_info(&m, s);
	write(fd, &m, 54);
	write(fd, s->img.data, m.bisizeimage);
	close(fd);
	return (m);
}
