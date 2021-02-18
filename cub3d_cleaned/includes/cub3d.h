/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:51:24 by spark             #+#    #+#             */
/*   Updated: 2021/02/18 15:30:01 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "cub3d_macro.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_point
{
	double pos_X;
	double pos_Y;
	double dir_X;
	double dir_Y;
	double plane_X;
	double plane_Y;
	
	double camera_X;
	double raydir_X;
	double raydir_Y;

	int		position_X;
	int		position_Y;

	double side_X;
	double side_Y;

	double deltadist_X;
	double deltadist_Y;
	double perpwalldist;

	int		step_X;
	int		step_Y;
	
	int		hit;
	int		hit_side;
	int		wall_face;
	
	int   texture[TEX_NUM][TEX_WIDTH * TEX_HEIGHT];
	double   step;
	double   texture_pos;
	
	double rotspeed;
	double movespeed;

	double *zBuffer;
}				t_point;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texnum;
}				t_sprite;

typedef struct s_spr_cast
{
		
	int			*spriteOrder;
	int			*spriteDistance;
	double	x;
	double	y;
	int		texnum;
	double  spriteX; 
	double  spriteY;
	double  invDet;
	double  transformX;
	double  transformY;
	int		spriteScreenX;
	int     uDiv;
    int     vDiv;
    double  vMove;
    int     vMoveScreen;
	int     spritescreenHeight;
	int     drawStartY;
	int     drawEndY;
	int     spritescreenWidth;
	int     drawStartX;
	int     drawEndX;
	int 	texX;
	int 	texY;
	int		d;
	int		spr_color;
	t_sprite *sprt;
}				t_spr_cast;

typedef struct s_cal_ray
{
	int		draw_start;
	int		draw_end;
	int		line_screenHeight;
	double	wallX;
}				t_cal_ray;

typedef struct s_flr
{
	int		x;
	double	w;
	int		i;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		center;
	float	posZ;
	float	rowDistance;
	float	floorStepX; 
	float	floorStepY; 
	float	floorX;
	float	floorY;
	int		tx;
	int		ty;
}				t_flr;

typedef struct s_tex
{
	int		texY;
	int		texX;
	int		texture_kind;
	int		floorTexture;
	int		ceilingTexture;
	int		color;
}				t_tex;

typedef struct	s_minfo
{
	int			s_width;
	int			s_height;
	int			m_width;
	int			m_height;
	int			num_sprite;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*sp_path;
	char		*f_path;
	char		*c_path;
	int			f_kind;
	int			c_kind;
	int			floor;
	int			ceiling;
}				t_minfo;
typedef struct	s_set
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			up;
	int			left;
	int			right;
	int			down;
	int			map1;
	int**		map2;
	char*		S_tex;
	char*		W_tex;
	char*		N_tex;
	char*		E_tex;
	char*		SPR_tex;
	int			F_corl;
	int			S_corl;
	t_img		img;
	t_point		p;
	t_spr_cast	spr;
	t_cal_ray	cr;
	t_flr		flr;
	t_tex		tex;
	t_minfo		minfo;
}				t_set;

// int worldMap[MAP_WIDTH][MAP_HEIGHT]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// t_sprite    spr[SPRITE_NUM] =
// {
//     {20.5, 11.5, 10}, //green light in front of playerstart
//     //green lights in every room
//     {18.5,4.5, 10},
//     {10.0,4.5, 10},
//     {10.0,12.5,10},
//     {3.5, 6.5, 10},
//     {3.5, 20.5,10},
//     {3.5, 14.5,10},
//     {14.5,20.5,10},
//     //row of pillars in front of wall: fisheye test
//     {18.5, 10.5, 9},
//     {18.5, 11.5, 9},
//     {18.5, 12.5, 9},

	
// 	{18.5, 12.5, 9},
// 	{19.5, 12.5, 9},
// 	{20.5, 12.5, 9},
// 	{21.5, 12.5, 9},
// 	{22.5, 12.5, 9},
// 	{23.5, 12.5, 9},
// 	{23.5, 12.5, 9},
// 	{24.5, 12.5, 9},
// 	{25.5, 12.5, 9},
// 	{26.5, 12.5, 9},
	

	
// 	//some barrels around the map
//     {21.5, 1.5, 8},
//     {15.5, 1.5, 8},
//     {16.0, 1.8, 8},
//     {16.2, 1.2, 8},
//     {3.5,  2.5, 8},
//     {9.5, 15.5, 8},
//     {10.0, 15.1,8},
//     {10.5, 15.8,8},

	
// };

#endif
