/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 12:08:59 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_incoming(t_color_c *in_light, t_color_c rayColor,
		t_material *material)
{
	t_color_c	emitting;

	emitting = color_scale(material->emission, material->emission_i);
	emitting = color_multiply(emitting, rayColor);
	*in_light = color_add(*in_light, emitting);
	if (in_light->b > 1)
		in_light->b /= 2;
	if (in_light->g > 1)
		in_light->g /= 2;
	if (in_light->r > 1)
		in_light->r /= 2;
}

t_color_c	ray_tracing(t_ray *ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hit_info;
	t_color_c	color;
	t_color_c	incoming_light;

	incoming_light = color_correct_new(0, 0, 0, 0);
	color = color_correct_new(0, 1, 1, 1);
	i = -1;
	while (++i < 20)
	{
		hit_info = intersections(minirt, ray, state);
		if (hit_info.hit)
		{
			ray->origin = hit_info.point;
			ray->direction = random_vec3_hs(hit_info.normal, state);
			// ray->direction = vec3_normalize(vec3_multiply(hit_info.normal,
			// 			random_vec3_hs(hit_info.normal, state)));
			calculate_incoming(&incoming_light, color, &hit_info.material);
			color = color_multiply(color, hit_info.material.color);
		}
		else
		{
			calculate_incoming(&incoming_light, color,
				&minirt->amb_light.material);
			break ;
		}
	}
	return (incoming_light);
}