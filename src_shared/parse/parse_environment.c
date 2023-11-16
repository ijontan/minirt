/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:16:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 18:23:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// our environment consists of: ambient lighting, camera and the light source
#include "minirt.h"

// p is short for the parse_info struct
void	parse_ambient_lighting(t_parse *p)
{
	p->amb_light.ratio = ft_atof(p->info[1], p);
	if (p->amb_light.ratio < 0.0 || p->amb_light.ratio > 1.0)
		exit_parse(p->info, "Ambient lighting", 'r');
	if (check_rgb(p->info[2], p))
		p->amb_light.color = color_correct((t_color)color_new(0, p->rgb[0],
					p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Ambient lighting", 'c');
}

void	parse_camera(t_parse *p)
{
	p->camera.origin = parse_coordinates(p->info[1], p);
	if (check_norm_vec_range(p->info[2], p))
		p->camera.direction = assign_norm_vec(p);
	else
		exit_parse(p->info, "Camera", 'n');
	p->camera.right = vec3_cross(p->camera.direction, vec3_new(0, 1, 0));
	p->camera.right = vec3_normalize(p->camera.right);
	p->camera.up = vec3_cross(p->camera.right, p->camera.direction);
	p->camera.vp_height = WINDOW_HEIGHT;
	p->camera.vp_width = WINDOW_WIDTH;
	p->camera.yaw = 0;
	p->camera.pitch = 0;
	p->camera.position = vec3_new(0, 0, 0);
	p->camera.fov = ft_atof(p->info[3], p);
	if (p->camera.fov < 0.0 || p->camera.fov > 180.0)
		exit_parse(p->info, "Camera", 'a');
	p->camera.fov = p->camera.fov * PI / 180.0;
}

void	parse_lighting(t_parse *p)
{
	t_pt_light	*pt_light;

	pt_light = ft_calloc(1, sizeof(t_pt_light));
	pt_light->position = parse_coordinates(p->info[1], p);
	pt_light->ratio = ft_atof(p->info[2], p);
	if (pt_light->ratio < 0.0 || pt_light->ratio > 1.0)
		exit_parse(p->info, "Lighting", 'r');
	if (check_rgb(p->info[3], p))
		pt_light->material.color = color_correct((t_color)color_new(0,
					p->rgb[0], p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Lighting", 'c');
	ft_lstadd_front(&p->pt_lights, ft_lstnew(pt_light));
}
