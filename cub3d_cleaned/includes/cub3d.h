/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:51:24 by spark             #+#    #+#             */
/*   Updated: 2021/02/22 23:51:54 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "cub3d_macro.h"
#include "cub3d_struct.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	draw_rect(t_set *set, int x, int y, int corl);
void	draw_all_rect(t_set *set);
void	parse_draw_map(t_set *s);

void	put_bmp_info(t_bmp *m, t_set *s);
t_bmp	make_bmp(t_set *s);

void	arrange_sprite(t_set *s);
int		key_press(int keycode, t_set *set);
int		key_release(int keycode, t_set *set);
void	key_action_2(t_set *s);
void	key_action(t_set *s);

void	make_window(t_set *s);
void	clean_screen(t_set *s);

void	map_side_check(t_set *set, char *line, unsigned char *flag, int i);
void	map_fcsr_check(t_set *set, char *line, unsigned char *flag, int i);
void	map_parse(t_set *set, char *map_name);

int		get_color(char *line);
int		get_fc(t_set *set, int kind, char *line);
int		error_msg(char *kind);
void	init_ck_map(t_set *set, int ***ck_map);
void	change_map(t_set *set, int **map, char *temp_map, int i);

int		flag_check(int start, int kind, unsigned char *flag, char *line);
int		check_map(t_set *set);
int		is_map(t_set *set, int **ck_map);
int		is_road(t_set *set, int ***ck_map, int x, int y);
void	get_map_size(t_set *set, int fd, int fd_2, char **line);

void	dir_setter(t_set *s, int x, int y);
void	set_pos(t_set *set, char pos);
int		get_map(int fd, char **line, t_set *set);

#endif
