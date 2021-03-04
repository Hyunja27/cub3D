/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:57:03 by spark             #+#    #+#             */
/*   Updated: 2021/03/04 18:39:29 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_side_check(t_set *set, char *line, unsigned char *flag, int i)
{
	if (ft_strnstr(line, "EA ", 3))
	{
		i = flag_check(3, EA_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("EA")) : 0;
		set->minfo.ea_path = ft_strdup(line + i);
	}
	if (ft_strnstr(line, "WE ", 3))
	{
		i = flag_check(3, WE_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("WE")) : 0;
		set->minfo.we_path = ft_strdup(line + i);
	}
	if (ft_strnstr(line, "SO ", 3))
	{
		i = flag_check(3, SO_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("SO")) : 0;
		set->minfo.so_path = ft_strdup(line + i);
	}
	if (ft_strnstr(line, "NO ", 3))
	{
		i = flag_check(3, NO_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("NO")) : 0;
		set->minfo.no_path = ft_strdup(line + i);
	}
}

void	map_fcsr_check(t_set *set, char *line, unsigned char *flag, int i)
{
	if (ft_strnstr(line, "F ", 2))
	{
		i = flag_check(2, FL_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("FL")) : 0;
		get_fc(set, FL_TEXT_NUM, line + i);
	}
	if (ft_strnstr(line, "C ", 2))
	{
		i = flag_check(2, CE_TEXT_NUM, flag, line);
		i < 0 ? exit(error_msg("CE")) : 0;
		get_fc(set, CE_TEXT_NUM, line + i);
	}
	if (ft_strnstr(line, "R ", 2))
	{
		i = flag_check(2, RE_NUM, flag, line);
		i < 0 ? exit(error_msg("R")) : 0;
		if ((set->minfo.s_width = ft_atoi(line + i)) < 0)
			return ;
		i += ft_ilencal(set->minfo.s_width);
		if ((set->minfo.s_height = ft_atoi(line + i)) < 0)
			return ;
	}
	set->minfo.s_height = (set->minfo.s_height <= 480) ? 480 : \
	set->minfo.s_height;
	set->minfo.s_width = (set->minfo.s_width <= 740) ? 740 : set->minfo.s_width;
}

void	map_parse_flagwhile(t_set *set, char **line, int fd, int *rt)
{
	int				i;
	unsigned char	flag;

	flag = 0;
	while (flag != 255 && (*rt = get_next_line(fd, line)) > 0)
	{
		map_side_check(set, *line, &flag, i);
		map_fcsr_check(set, *line, &flag, i);
		get_max_screen(set);
		if (ft_strnstr(*line, "S ", 2))
		{
			i = flag_check(2, SP_TEXT_NUM, &flag, *line);
			i < 0 ? exit(error_msg("SP")) : 0;
			set->minfo.sp_path = ft_strdup(*line + i);
		}
	}
}

int		map_parse(t_set *set, char *map_name)
{
	char			*line;
	int				fd;
	int				rt;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		printf("\n\nI can't find map file! where is it..? is it right name?\n");
		return (1);
	}
	line = 0;
	map_parse_flagwhile(set, &line, fd, &rt);
	free(line);
	if (rt <= 0)
	{
		printf("\n\nMap file is exist, But it's Data is \
		Not appropriate! Sorry!\n\n");
		return (1);
	}
	while (line[0] != ' ' && !ft_isdigit(line[0]))
		get_next_line(fd, &line);
	get_map(fd, &line, set);
	close(fd);
	free(line);
	return (0);
}
