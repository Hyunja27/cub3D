/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:58:20 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 15:20:24 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sound_bgm(void)
{
	system("afplay sounds/DarkOutside.mp3 &");
}

void	sound_effect(int i)
{
	if (i == 1)
		system("afplay sounds/intro.wav &");
	if (i == 2)
		system("afplay sounds/outro.wav");
	if (i == 3)
		system("afplay sounds/hit.wav &");
	if (i == 4)
		system("afplay sounds/slide.wav &");
}
