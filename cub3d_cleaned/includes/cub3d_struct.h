/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:51:29 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 17:03:08 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

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
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;

	double camerax;
	double raydirx;
	double raydiry;

	int		positionx;
	int		positiony;

	int		hid_x;
	int		hid_y;

	double sidex;
	double sidey;

	double deltadistx;
	double deltadisty;
	double perpwalldist;

	int		stepx;
	int		stepy;

	int		hit;
	int		hit_side;
	int		wall_face;

	int		texture[TEX_NUM][TEX_WIDTH * TEX_HEIGHT];
	double	step;
	double	texture_pos;
	
	double rspd;
	double movespeed;

	double *zBuffer;
	int		secret;
}				t_point;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texnum;
}				t_sprite;

typedef struct		s_spr_cast
{
	int			*spriteorder;
	int			*spritedistance;
	double		x;
	double		y;
	int			texnum;
	double		sp_x;
	double		sp_y;
	double		invdet;
	double		tr_x;
	double		tr_y;
	int			spritescreenx;
	int			udiv;
	int			vdiv;
	double		vmove;
	int			vmovescreen;
	int			sp_sc_h;
	int			drawstarty;
	int			drawendy;
	int			sp_sc_w;
	int			drawstartx;
	int			drawendx;
	int			texx;
	int			texy;
	int			d;
	int			spr_color;
	t_sprite	*sprt;
}					t_spr_cast;

typedef struct		s_cal_ray
{
	int		draw_start;
	int		draw_end;
	int		line_screenheight;
	double	wallx;
}					t_cal_ray;

typedef struct	s_flr
{
	int		x;
	double	w;
	int		i;
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	int		center;
	float	posz;
	float	rowdistance;
	float	floorstepx;
	float	floorstepy;
	float	floorx;
	float	floory;
	int		tx;
	int		ty;
}				t_flr;

typedef struct	s_tex
{
	int		texy;
	int		texx;
	int		texture_kind;
	int		floortexture;
	int		ceilingtexture;
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

# pragma pack(push, 1)

typedef struct	s_bmp
{
	unsigned char	bftype1;
	unsigned char	bftype2;
	unsigned int	bfsize;
	unsigned short	bfreserved1;
	unsigned short	bfreserved2;
	unsigned int	bfoffbits;
	unsigned int	bisize;
	int				biwidth;
	int				biheight;
	unsigned short	biplanes;
	unsigned short	bibitcount;
	unsigned int	bicompression;
	unsigned int	bisizeimage;
	int				bixpelspermeter;
	int				biypelspermeter;
	unsigned int	biclrused;
}				t_bmp;

# pragma pack(pop)

typedef struct	s_set
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			up;
	int			left;
	int			right;
	int			down;
	int			updown;
	int			jump;
	int			q_action;
	int			door;
	int			door_end;
	int			up_arrow;
	int			left_arrow;
	int			right_arrow;
	int			down_arrow;
	int			space;
	int			jump_end;
	int			map1;
	int**		map2;
	char*		s_tex;
	char*		w_tex;
	char*		n_tex;
	char*		e_tex;
	char*		spr_tex;
	char*		map_path;
	int			save_flag;
	int			f_corl;
	int			s_corl;
	double		life;
	int			time;
	long		msec;
	int			collision;
	int			next_stage;
	double		olddir_x;
	double		olddir_y;
	double		oldplane_x;
	t_img		img;
	t_point		p;
	t_spr_cast	spr;
	t_cal_ray	cr;
	t_flr		flr;
	t_tex		tex;
	t_minfo		minfo;
}				t_set;

#endif
