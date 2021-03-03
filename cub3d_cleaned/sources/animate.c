/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:56:10 by spark             #+#    #+#             */
/*   Updated: 2021/03/03 23:16:37 by spark            ###   ########.fr       */
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
		s->time = 15;
	else if (t % 3)
		s->time = 9;
	else if (t % 5)
		s->time = 7;
	else
		s->time = 0;
}
