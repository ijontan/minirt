/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:31 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/30 00:06:46 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// parse conditions:
// - need at least a plane, sphere and cylinder
// - each type of element can be separated by one or more line breaks
// - each type of element can be set in any order in the file
// - elements which are defined by a capital letter can only be declared once 
// in the scene

// mand_flag: flag and check if all minimum requirements of a scene are present
static bool parse_line(char *line, t_parse *p)
{
	int		i;

	p->info = ft_split(line, ' ');
	i = -1;
	while (i < 6)
	{
		if (!ft_strncmp(p->info[0], p->obj_type[i], ft_strlen(p->info[0])))
		{
			check_line_format(p->info[0], p);
			p->func_ptr[i](p);
			free_2darray(info);
			return (true);
		}
	}
	printf("\e[0;31mError: Unknown object \e[0m%s\n", info[0]);
	free_2darray(info);
	return (false);
}

static int open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("\e[0;31mError: unable to open .rt file\e[0m\n")
		return (0);
	}
	return (fd);
}

static void	init_parsing(t_parse *parse_info)
{
	int	i;

	i = -1;
	while (++i < 6)
		parse_info->mand_flag[i] = 0;
	parse_info->obj_type[0] = "A";
	parse_info->obj_type[1] = "C";
	parse_info->obj_type[2] = "L";
	parse_info->obj_type[3] = "pl";
	parse_info->obj_type[4] = "sp";
	parse_info->obj_type[5] = "cy";
	parse_info->func_ptr[0] = parse_ambient_lighting;
	parse_info->func_ptr[1] = parse_camera;
	parse_info->func_ptr[2] = parse_lighting;
	parse_info->func_ptr[3] = parse_plane;
	parse_info->func_ptr[4] = parse_sphere;
	parse_info->func_ptr[5] = parse_cylinder;
}

bool parse_rt_file(char *infile, t_parse *parse_info)
{
	char	*buff;

	parse_info->infile_fd = open_infile(infile);
	if (parse_info->infile_fd == 0)
		return (false);
	init_parsing(parse_info);
	buff = get_next_line(parse_info->infile_fd);
	while (buff)
	{
		if (!parse_line(buff, parse_info))
		{
			free(buff);
			return (false);
		}
		free(buff);
		buff = get_next_line(parse_info->infile_fd);
	}
	free(buff);
	return (true);
}