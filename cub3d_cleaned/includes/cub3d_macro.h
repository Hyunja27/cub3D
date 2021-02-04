/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macro.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:51:29 by spark             #+#    #+#             */
/*   Updated: 2021/02/04 15:52:33 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MACRO_H
# define CUB3D_MACRO_H

#define BOX_SIZE 40
#define MAP_BOX_SIZE 10

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TEX_NUM 11
#define SPRITE_NUM 29

#define COLS 24
#define ROWS 24
#define BOX_WIDTH (MAP_BOX_SIZE * COLS)
#define BOX_HEIGHT (MAP_BOX_SIZE * ROWS)

#define ESC_KEY 53
#define UP_KEY 13
#define DOWN_KEY 1
#define LEFT_KEY 0
#define RIGHT_KEY 2
#define SPACE_KEY 49
#define M_KEY 46
#define C_KEY 8
#define E_KEY 14
#define Q_KEY 12
#define F_KEY 3
#define R_KEY 15
#define KeyPress    2
#define KeyRelease  3

#define START_POSITION_X (WIDTH - (BOX_SIZE * 2))
#define START_POSITION_Y (HEIGHT - (BOX_SIZE * 2))

#define CLR_LBL 0xadd8e6
#define CLR_CRD 0xdc143c
#define CLR_ORG 0xff8c00
#define CLR_DGR 0x8fbc8f
#define CLR_KAK 0xbdb76b

#endif