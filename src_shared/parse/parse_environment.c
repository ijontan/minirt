/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:16:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 18:09:55 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// our environment consists of: ambient lighting, camera and the light source
#include "minirt.h"

// p is short for the parse_info struct
void parse_ambient_lighting(char **info, t_parse *p)
{
	p->amb_light->ratio = ft_atof(info[1]);
	if (p->amb_light->ratio < 0.0 || p->amb_light->ratio > 1.0)
		exit_parse(info, "A-r");
	if (check_rgb(info[2], p))
		p->amb_light->material->color = color_correct(\
			(t_color)color_new(0, p->rgb[0], p->rgb[1], p->rgb[2]))
	else
		exit_parse(info, "A-c");
	p->mand_flag[0] = 1;
}

void parse_camera(char **info, t_parse *p)
{
	p->cam->origin = parse_coordinates(info[1]);
	if (check_normalized(info[2], p))
		p->cam->direction = assign_norm_vec(p);
	else
		exit_parse(info, "C-n");
	// [0.0, 1.0]
	p->cam->fov = ft_atof(info[3]);
	// [0.0, 180.0]
	p->mand_flag[1] = 1;
}

void parse_lighting(char **info, t_parse *p)
{
	p->light_source->position = parse_coordinates(info[1]);
	// integers, floats with .0
	p->light_source->ratio = ft_atof(info[2]);
	// [0.0, 1.0]
	p->light_source->material->color = parse_color(info[3]);
	// [0, 255] (bonus)
	p->mand_flag[2] = 1;
}
