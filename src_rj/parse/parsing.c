/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:31 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 09:21:45 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// parse conditions:
// - need at least a plane, sphere and cylinder
// - each type of element can be separated by one or more line breaks
// - each type of element can be set in any order in the file
// - elements which are defined by a capital letter can only be declared once 
// in the scene

static bool parse_line(char *line, t_parse *parse_info)
{
	char **info;

	info = ft_split(line, ' ');
	if (!ft_strncmp(info[0], "A", ft_strlen(info[0])))
		parse_ambient_lighting(info, parse_info);
	else if (!ft_strncmp(info[0], "C", ft_strlen(info[0])))
		parse_camera(info, parse_info);
	else if (!ft_strncmp(info[0], "L", ft_strlen(info[0])))
		parse_light(info, parse_info);
	else if (!ft_strncmp(info[0], "pl", ft_strlen(info[0])))
		parse_plane(info, parse_info);
	else if (!ft_strncmp(info[0], "sp", ft_strlen(info[0])))
		parse_sphere(info, parse_info);
	else if (!ft_strncmp(info[0], "cy", ft_strlen(info[0])))
		parse_cylinder(info, parse_info);
	else
	{
		printf("\e[0;31mError: Unknown object \e[0m%s", info[0]);
		free_2darray(info);
		return (false);
	}
	free_2darray(info);
	return (true);
}

static int open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("\e[0;31mError: unable to open .rt file\e[0m")
		return (0);
	}
	return (fd);
}

static void	init_mand_flag(t_parse *parse_info)
{
	int	i;

	i = -1;
	while (++i < 6)
		parse_info->mand_flag[i] = 0;
}

bool parse_rt_file(char *infile, t_parse *parse_info)
{
	char	*buff;

	parse_info->infile_fd = open_infile(infile);
	if (parse_info->infile_fd == 0)
		return (false);
	init_mand_flag(parse_info);
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
