/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:16:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 09:21:45 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// our environment consists of: ambient lighting, camera and the light source
#include "minirt.h"

// p is short for the parse_info struct
void parse_ambient_lighting(char **info, t_parse *p)
{
	p->amb_light->lighting_ratio = ft_atof(info[1]);
	p->amb_light->color = parse_color(info[2]);
	// [0, 255]
	p->mand_flag[0] = 1;
}
// p->temp_f = ft_atof(info[1]);
// if (p->temp_f < 0.0 || p->temp_f > 1.0)
// 	p->amb_light->lighting_ratio = p->temp_f;
// else
// {
// 	printf("Error: Ambient lighting ratio out of range [0.0, 1.0]");
// 	free_2darray(info);
// 	exit(EXIT_FAILURE);
// }

void parse_camera(char **info, t_parse *p)
{
	p->cam->origin = parse_coordinates(info[1]);
	// integers, floats with .0
	p->cam->direction = parse_coordinates(info[2]);
	// [0.0, 1.0]
	p->cam->fov = ft_atof(info[3]);
	// [0.0, 180.0]
	p->mand_flag[1] = 1;
}

void parse_lighting(char **info, t_parse *p)
{
	p->light_source->position = parse_coordinates(info[1]);
	// integers, floats with .0
	p->light_source->brightness_ratio = ft_atof(info[2]);
	// [0.0, 1.0]
	p->light_source->color = parse_color(info[3]);
	// [0, 255] (bonus)
	p->mand_flag[2] = 1;
}
