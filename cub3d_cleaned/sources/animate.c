/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:56:10 by spark             #+#    #+#             */
/*   Updated: 2021/03/04 21:03:32 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	time_move(t_set *s)
{
	time_t	t;
	double	l;

	time(&t);
	l = (double)t;
	if (t % 3 == 0)
		s->time = 11;
	else if (t % 7 == 0)
		s->time = 8;
	else if (t % 11 == 0)
		s->time = 4;
	else if (t % 2 == 0)
		s->time = -2;
	else
		s->time = 0;
}
