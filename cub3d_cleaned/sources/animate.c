/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:56:10 by spark             #+#    #+#             */
/*   Updated: 2021/03/04 20:45:57 by spark            ###   ########.fr       */
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
	if (t % 2 == 0)
		s->time = 8;
	else if (t % 3 == 0)
		s->time = -9;
	else if (t % 5)
		s->time = 3;
	else
		s->time = 0;
}
