/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:23:50 by spark             #+#    #+#             */
/*   Updated: 2021/02/26 11:31:20 by spark            ###   ########.fr       */
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
	free(set->S_tex);
	free(set->W_tex);
	free(set->N_tex);
	free(set->E_tex);
	free(set->SPR_tex);
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
	free(set->spr.spriteDistance);
	free(set->spr.spriteOrder);
}
