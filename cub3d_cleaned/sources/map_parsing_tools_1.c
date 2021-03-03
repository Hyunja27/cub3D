/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:57:03 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 18:06:57 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	while (*line != ',' && *line)
	{
		line++;
		if (!(*line))
			return (-1);
	}
	g = ft_atoi(++line);
	while (*line != ',' && *line)
	{
		line++;
		if (!(*line))
			return (0);
	}
	b = ft_atoi(++line);
	return ((r * 256 * 256) + (g * 256) + b);
}

int		get_fc(t_set *set, int kind, char *line)
{
	int	temp;

	if (ft_isdigit(*line))
	{
		(kind == FL_TEXT_NUM) ? (set->minfo.f_kind = 0) : (set->minfo.c_kind = 0);
		(kind == FL_TEXT_NUM) ? (set->minfo.floor = get_color(line)) : (set->minfo.ceiling = get_color(line));
		temp = (kind == FL_TEXT_NUM) ? set->minfo.floor : set->minfo.ceiling;
		if (temp < 0)
			return (0);
	}
	else if (*line == '.')
	{
		(kind == FL_TEXT_NUM) ? (set->minfo.f_kind = 1) : (set->minfo.c_kind = 1);
		(kind == FL_TEXT_NUM) ? (set->minfo.f_path = ft_strdup(line)) : (set->minfo.c_path = ft_strdup(line));
	}
	return (1);
}

int		error_msg(char *kind)
{
	printf("\n\nOh... I found something to fix!\n \
	-> %s information is double entered!! \n\n", kind);
	return (0);
}

void	init_ck_map(t_set *set, int ***ck_map)
{
	int i;
	int j;
	int a;

	i = 0;
	a = 5;
	while (i < (set->minfo.m_height + 2))
	{
		j = 0;
		while (j < (set->minfo.m_width + 2))
		{
			if (i == 0 || j == 0 || i == set->minfo.m_height + 1 || j == set->minfo.m_width + 1)
			{
				(*ck_map)[i][j] = -1;
			}
			else
			{
				if (set->map2[i - 1][j - 1] == 2)
				{
					set->spr.sprt[a].x = i - 1 + 0.5;
					set->spr.sprt[a].y = j - 1 + 0.5;
					set->spr.sprt[a].texnum = 9;
					a++;
				}
				else if (set->map2[i - 1][j - 1] == 9)
				{
					set->spr.sprt[a].x = i - 1;
					set->spr.sprt[a].y = j - 1;
					set->spr.sprt[a].texnum = 7;
					a++;
				}
				(*ck_map)[i][j] = set->map2[i - 1][j - 1];
			}
			j++;
		}
		i++;
	}
}

void	change_map(t_set *set, int **map, char *temp_map, int i)
{
	int j;

	j = -1;
	while (++j < set->minfo.m_width)
		(*map)[j] = -1;
	j = -1;
	while (temp_map[++j] != 0)
	{
		if (temp_map[j] == 'E' || temp_map[j] == 'W' || \
		temp_map[j] == 'S' || temp_map[j] == 'N')
		{
			set_pos(set, temp_map[j]);
			set->p.posX = i;
			set->p.posY = j;
			temp_map[j] = '0';
		}
		(*map)[j] = temp_map[j] == ' ' ? -1 : temp_map[j] - '0';
		if ((*map)[j] == 2)
			set->minfo.num_sprite++;
	}
}
