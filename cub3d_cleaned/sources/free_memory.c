/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:23:50 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:00:40 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_memory(t_set *set)
{
	int i;

	i = 0;
	while (i < set->minfo.m_height)
		free(set->map2[i++]);
	free(set->map2);
	free(set->s_tex);
	free(set->w_tex);
	free(set->n_tex);
	free(set->e_tex);
	free(set->spr_tex);
	free(set->minfo.no_path);
	free(set->minfo.so_path);
	free(set->minfo.we_path);
	free(set->minfo.ea_path);
	free(set->minfo.sp_path);
	if (!set->minfo.f_path)
		free(set->minfo.f_path);
	if (!set->minfo.c_path)
		free(set->minfo.c_path);
	free(set->p.zBuffer);
	free(set->spr.sprt);
}
