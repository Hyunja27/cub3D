/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:57:03 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:11:26 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_setter(t_set *s, int x, int y)
{
	s->p.dirx = x;
	s->p.diry = y;
}

void	set_pos(t_set *set, char pos)
{
	if (pos == 'E')
	{
		dir_setter(set, 0, 1);
		set->p.planex = 0.66;
		set->p.planey = 0;
	}
	if (pos == 'W')
	{
		dir_setter(set, 0, -1);
		set->p.planex = -0.66;
		set->p.planey = 0;
	}
	if (pos == 'S')
	{
		dir_setter(set, 1, 0);
		set->p.planex = 0;
		set->p.planey = -0.66;
	}
	if (pos == 'N')
	{
		dir_setter(set, -1, 0);
		set->p.planex = 0;
		set->p.planey = 0.66;
	}
}

int		get_map(int fd, char **line, t_set *set)
{
	int		i;
	int		fd_2;
	char	*temp_map;

	i = -1;
	fd_2 = open("tmp_map", O_CREAT | O_RDWR | O_TRUNC, 0777);
	get_map_size(set, fd, fd_2, line);
	set->map2 = (int **)malloc(sizeof(int *) * set->minfo.m_height);
	while (++i < set->minfo.m_height)
		set->map2[i] = (int *)malloc(sizeof(int) * set->minfo.m_width);
	close(fd_2);
	fd_2 = open("tmp_map", O_RDONLY);
	i = 0;
	while ((get_next_line(fd_2, &temp_map) > 0))
	{
		change_map(set, &(set->map2[i]), temp_map, i);
		i++;
		free(temp_map);
	}
	free(temp_map);
	close(fd_2);
	set->minfo.num_sprite += 5;
	set->spr.sprt = (t_sprite *)malloc(sizeof(t_sprite) *\
	set->minfo.num_sprite);
	return (1);
}
