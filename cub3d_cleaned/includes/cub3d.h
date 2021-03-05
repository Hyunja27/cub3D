/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:51:24 by spark             #+#    #+#             */
/*   Updated: 2021/03/05 16:19:43 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_macro.h"
# include "cub3d_struct.h"
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# define _USE_MATH_DEFINES

void	carl_ray(t_set *s);
void	carl_ray_2(t_set *s, int *tmp, int i, int x);

void	draw_rect(t_set *set, int x, int y, int corl);
void	draw_all_rect(t_set *set);
void	parse_draw_map(t_set *s);

void	put_bmp_info(t_bmp *m, t_set *s);
t_bmp	make_bmp(t_set *s);

void	arrange_sprite(t_set *s);
int		key_press(int keycode, t_set *set);

int		key_release(int keycode, t_set *set);
int		key_release_2(int keycode, t_set *set);
int		key_exit(t_set *set);

void	key_action_2(t_set *s);
void	key_action(t_set *s);

void	make_window(t_set *s);
void	clean_screen(t_set *s);

void	map_side_check(t_set *set, char *line, unsigned char *flag, int i);
void	map_fcsr_check(t_set *set, char *line, unsigned char *flag, int i);
int		map_parse(t_set *set, char *map_name);
void	hit_check_2(t_set *s);

int		get_color(char *line);
int		get_fc(t_set *set, int kind, char *line);
void	get_fc_2(t_set *set, int kind, char *line);
int		error_msg(char *kind);
void	init_ck_map(t_set *set, int ***ck_map);
void	init_ck_map_2(t_set *set, int i, int j, int *a);
void	change_map(t_set *set, int **map, char *temp_map, int i);

int		flag_check(int start, int kind, unsigned char *flag, char *line);
int		check_map(t_set *set);
void	check_map_2(t_set *set);
int		is_map(t_set *set, int **ck_map);
int		is_road(t_set *set, int ***ck_map, int x, int y);
void	get_map_size(t_set *set, int fd, int fd_2, char **line);

void	dir_setter(t_set *s, int x, int y);
void	set_pos(t_set *set, char pos);
int		get_map(int fd, char **line, t_set *set);

int		load_file(t_set *set, int num, char *path);
void	load_tex(t_set *set);

int		main_loop(t_set *set);

void	sprite_cast_end(t_set *s, int x, int y, int i);
void	sprite_cast(t_set *s);
void	sprite_cast_insert_1(t_set *s, int i);
void	sprite_cast_insert_2(t_set *s, int i);

void	carl_ray(t_set *s);
void	carl_fc(t_set *s);

void	free_memory(t_set *set);

void	init_basic_2(t_set *set);
int		init_basic(t_set *set, int ac, char *av[]);

void	get_max_screen(t_set *s);

void	sound_bgm(void);
void	sound_effect(int i);

void	draw_lifebar(t_set *set, int x, int y, int corl);
void	parse_draw_lifebar(t_set *s);
void	draw_all_rect_lifebar(t_set *set);
void	draw_life(t_set *set);

void	time_move(t_set *s);
void	secret_check(t_set *s);
int		make_darker(int color, int size);
void	updown_protect(t_set *s);
void	collision_damage(t_set *s, double *pos, double m);
void	jump_door(t_set *s);
void	exit_cub3d(void);

#endif
