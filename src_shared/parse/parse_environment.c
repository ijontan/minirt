/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:16:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 23:24:50 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// our environment consists of: ambient lighting, camera and the light source
#include "minirt.h"

// p is short for the parse_info struct
void parse_ambient_lighting(t_parse *p)
{
	p->amb_light->ratio = ft_atof(p->info[1]);
	if (p->amb_light->ratio < 0.0 || p->amb_light->ratio > 1.0)
		exit_parse(p->info, "Ambient lighting", 'r');

	if (check_rgb(p->info[2], p))
		p->amb_light->material->color = color_correct(\
			(t_color)color_new(0, p->rgb[0], p->rgb[1], p->rgb[2]))
	else
		exit_parse(p->info, "Ambient lighting", 'c');

	p->mand_flag[0] = 1;
}

void parse_camera(t_parse *p)
{
	p->cam->origin = parse_coordinates(p->info[1]);

	if (check_normalized(p->info[2], p))
		p->cam->direction = assign_norm_vec(p);
	else
		exit_parse(p->info, "Camera", 'n');
	
	p->cam->fov = ft_atof(p->info[3]);
	if (p->cam->fov < 0.0 || p->cam->fov > 180.0)
		exit_parse(p->info, "Camera", 'a');
	p->cam->fov = p->cam->fov * 3.14159 / 180.0;
	
	p->mand_flag[1] = 1;
}

void parse_lighting(t_parse *p)
{
	p->light_source->position = parse_coordinates(p->info[1]);

	p->light_source->ratio = ft_atof(p->info[2]);
	if (p->light_source->ratio < 0.0 || p->light_source->ratio > 1.0)
		exit_parse(p->info, "Lighting", 'r');

	if (check_rgb(p->info[3], p))
		p->light_source->material->color = color_correct(\
			(t_color)color_new(0, p->rgb[0], p->rgb[1], p->rgb[2]))
	else
		exit_parse(p->info, "Lighting", 'c');

	p->mand_flag[2] = 1;
}
