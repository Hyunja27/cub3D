/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:56:10 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 17:16:20 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	time_move(t_set *s)
{
	time_t	t;

	time(&t);

	if (t % 2)
		s->time = 4;
	else
		s->time = 0;
}