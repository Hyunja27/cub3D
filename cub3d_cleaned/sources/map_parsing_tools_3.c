/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:57:03 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:21:14 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		exit_cub3d(void)
{
	system("leaks cub3D");
	exit(0);
}

void		get_fc_2(t_set *set, int kind, char *line)
{
	if (kind == FL_TEXT_NUM)
	{
		(set->minfo.f_kind = 1);
		(set->minfo.f_path = ft_strdup(line));
	}
	else
	{
		(set->minfo.c_kind = 1);
		(set->minfo.c_path = ft_strdup(line));
	}
}

void		init_ck_map_2(t_set *set, int i, int j, int *a)
{
	if (set->map2[i - 1][j - 1] == 2)
	{
		set->spr.sprt[*a].x = i - 1 + 0.5;
		set->spr.sprt[*a].y = j - 1 + 0.5;
		set->spr.sprt[*a].texnum = 9;
		(*a)++;
	}
	else if (set->map2[i - 1][j - 1] == 9)
	{
		set->p.hid_x = i - 1;
		set->p.hid_y = j - 1;
	}
}

void		check_map_2(t_set *set)
{
	set->spr.sprt[0].y = (int)(set->minfo.m_width / 2) + 0.5;
	set->spr.sprt[0].x = (int)(set->minfo.m_height / 2) + 0.5;
	set->map2[(int)set->spr.sprt[0].x][(int)set->spr.sprt[0].y] = 3;
	set->spr.sprt[0].texnum = 5;
	set->spr.sprt[1].y = (int)(set->minfo.m_width / 3) + 0.5;
	set->spr.sprt[1].x = (int)(set->minfo.m_height / 6) + 0.5;
	set->map2[(int)set->spr.sprt[1].x][(int)set->spr.sprt[1].y] = 3;
	set->spr.sprt[1].texnum = 4;
	set->spr.sprt[2].y = (int)(set->minfo.m_width / 5) + 0.5;
	set->spr.sprt[2].x = (int)(set->minfo.m_height / 2) + 0.5;
	set->map2[(int)set->spr.sprt[2].x][(int)set->spr.sprt[2].y] = 3;
	set->spr.sprt[2].texnum = 5;
	set->spr.sprt[3].y = (int)(set->minfo.m_width / 7) + 0.5;
	set->spr.sprt[3].x = (int)(set->minfo.m_height / 3) + 0.5;
	set->map2[(int)set->spr.sprt[3].x][(int)set->spr.sprt[3].y] = 3;
	set->spr.sprt[3].texnum = 4;
	set->spr.sprt[4].y = (int)(set->minfo.m_width / 5) + 0.5;
	set->spr.sprt[4].x = (int)(set->minfo.m_height / 2) + 0.5;
	set->map2[(int)set->spr.sprt[4].x][(int)set->spr.sprt[4].y] = 3;
	set->spr.sprt[4].texnum = 5;
}
