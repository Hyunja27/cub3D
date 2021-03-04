/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:57:03 by spark             #+#    #+#             */
/*   Updated: 2021/03/04 20:09:23 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		flag_check(int start, int kind, unsigned char *flag, char *line)
{
	if (((*flag) >> kind & 1) == 1)
		return (-1);
	while (line[start] == ' ' || line[start] == '	')
		start++;
	(*flag) |= 1 << kind;
	return (start);
}

int		check_map(t_set *set)
{
	int **ck_map;
	int i;
	int rt;

	ck_map = (int **)malloc(sizeof(int *) * (set->minfo.m_height + 2));
	i = -1;
	while (++i < set->minfo.m_height + 2)
		ck_map[i] = (int *)malloc(sizeof(int) * (set->minfo.m_width + 2));
	init_ck_map(set, &ck_map);
	check_map_2(set);
	i = -1;
	rt = is_map(set, ck_map);
	i = 0;
	while (i < set->minfo.m_height + 2)
		free(ck_map[i++]);
	free(ck_map);
	if (!(set->p.zBuffer = malloc(sizeof(double) * set->minfo.s_width)))
		return (-1);
	return (rt);
}

int		is_map(t_set *set, int **ck_map)
{
	int is_zero;
	int i;
	int j;

	is_zero = 0;
	i = -1;
	while (++i < set->minfo.m_height)
	{
		j = -1;
		while (++j < set->minfo.m_width)
		{
			if (ck_map[i][j] == 0)
			{
				is_zero = 1;
				if (is_road(set, &ck_map, i, j) == 0)
					return (0);
			}
		}
	}
	if (!is_zero)
		return (0);
	else
		return (1);
}

int		is_road(t_set *set, int ***ck_map, int x, int y)
{
	int dir_x[4];
	int dir_y[4];
	int i;

	dir_x[0] = -1;
	dir_x[1] = 0;
	dir_x[2] = 1;
	dir_x[3] = 0;
	i = -1;
	while (++i < 4)
		dir_y[3 - i] = dir_x[i];
	i = -1;
	if ((*ck_map)[x][y] == 1 || (*ck_map)[x][y] == -2)
		return (1);
	if ((*ck_map)[x][y] == -1)
		return (0);
	(*ck_map)[x][y] = -2;
	i = -1;
	while (++i < 4)
		if (!is_road(set, ck_map, x + dir_x[i], y + dir_y[i]))
			return (0);
	return (1);
}

void	get_map_size(t_set *set, int fd, int fd_2, char **line)
{
	int temp_size;

	set->minfo.m_height = 0;
	set->minfo.m_width = 0;
	temp_size = ft_strlen(*line);
	if (set->minfo.m_width < temp_size)
		set->minfo.m_width = temp_size;
	set->minfo.m_height++;
	write(fd_2, *line, temp_size);
	write(fd_2, "\n", 1);
	free(*line);
	while ((get_next_line(fd, line)) > 0)
	{
		temp_size = ft_strlen(*line);
		if (set->minfo.m_width < temp_size)
			set->minfo.m_width = temp_size;
		set->minfo.m_height++;
		write(fd_2, *line, temp_size);
		write(fd_2, "\n", 1);
		if (*line)
			free(*line);
	}
}
