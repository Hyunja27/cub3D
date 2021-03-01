/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:58:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/01 14:40:45 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sound_bgm(void)
{
	system("afplay sounds/drum.wav &");
}

void	sound_effect(int i)
{
	if (i == 1)
		system("afplay sounds/intro.wav &");
	if (i == 2)
		system("afplay sounds/flute_end.wav");
}
