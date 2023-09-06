/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 23:32:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_incoming(t_color_c *in_light, t_color_c rayColor,
		t_material *material)
{
	t_color_c	emitting;
	static int	count;

	if (count < 100)
		printf("count: %d \ninlight: %f %f %f\n", count, in_light->r,
			in_light->g, in_light->b);
	emitting = color_scale(material->emission, 0.1);
	if (count < 100)
		printf("emitting: %f %f %f\n", emitting.r, emitting.g, emitting.b);
	emitting = color_multiply(emitting, rayColor);
	*in_light = color_add(*in_light, emitting);
	if (in_light->b > 1.0f)
		in_light->b = 1.0f;
	if (in_light->g > 1.0f)
		in_light->g = 1.0f;
	if (in_light->r > 1.0f)
		in_light->r = 1.0f;
	if (count++ < 100)
	{
		printf("color: %f %f %f\n", rayColor.r, rayColor.g, rayColor.b);
		printf("emitting: %f %f %f\n", emitting.r, emitting.g, emitting.b);
		printf("light: %f %f %f\n\n", in_light->r, in_light->g, in_light->b);
	}
}

t_color_c	ray_tracing(t_ray *ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hit_info;
	t_color_c	color;
	t_color_c	incoming_light;

	incoming_light = color_correct_new(0, 0, 0, 0);
	color = color_correct_new(0, 1.0f, 1.0f, 1.0f);
	i = -1;
	while (++i < 2)
	{
		hit_info = intersections(minirt, ray, state);
		if (hit_info.hit)
		{
			ray->origin = hit_info.point;
			ray->direction = random_vec3_hs(hit_info.normal, state);
			ray->direction = vec3_add(ray->direction, hit_info.normal);
			// ray->direction = vec3_normalize(vec3_cross(hit_info.normal,
			// 		random_vec3_hs(hit_info.normal, state)));
			calculate_incoming(&incoming_light, color, &hit_info.material);
			color = color_multiply(color, hit_info.material.color);
			// color = color_scale(color, 0.5f);
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

// t_color_c	ray_tracing(t_ray *ray, t_minirt *minirt, unsigned int *state)
// {
// 	t_hit_info	hit_info;
// 	t_color_c	color;
// 	t_color_c	incoming_light;

// 	hit_info = intersections(minirt, ray, state);
// 	if (hit_info.hit)
// 	{
// 		ray->origin = hit_info.point;
// 		ray->direction = random_vec3_hs(hit_info.normal, state);
// 		return (ray_tracing(ray, minirt, state));
// 	}
// 	incoming_light = color_correct_new(0, 0, 0, 0);
// 	color = color_correct_new(0, 1.0f, 1.0f, 1.0f);

// }
