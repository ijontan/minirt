/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/10/02 19:09:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	calculate_incoming(t_color_c *in_light, t_color_c *rayColor, t_material *material,
		t_minirt *rt, t_hit_info *hi)
// void	calculate_incoming(t_color_c *in_light, t_color_c *rayColor,
// 		t_material *material)
{
	t_color_c	emitting;
	t_color_c	point_color;

	// emitting = get_color(minirt, hit_info);
	emitting = material->emission;
	// emitting = color_add(material->emission, emitting);
	// printf("color: %f %f %f\n", emitting.r, emitting.g, emitting.b);
	emitting = color_scale(emitting, material->emission_i);
	// emitting = phong_reflection(minirt, hit_info);
	emitting = color_multiply(emitting, *rayColor);
	*in_light = color_add(*in_light, emitting);
	point_color = get_lights_color(rt, hi);
	emitting = color_multiply(point_color, *rayColor);
	emitting = color_scale(emitting, 0.5f);
	*in_light = color_add(*in_light, emitting);
	*rayColor = color_multiply(*rayColor, point_color);
	(void)rt;
	(void)hi;
}

t_color_c	get_env_light(t_ray *ray, bool is_env)
{
	float	t;

	if (!is_env && ray->direction.y > 0.0f)
		return (color_correct_new(0, 1, 1, 1));
	else if (!is_env && ray->direction.y < 0.0f)
		return (color_correct_new(0, 0.1, 0.1, 0.1));
	if (ray->direction.y < 0.0f)
		return (color_correct_new(0, 0.1, 0.1, 0.1));
	t = bazier_curves_1d_cubic(0.5f * (ray->direction.y + 1.0f),
								(double[]){0, -3, 3.5, 1});
	return (color_tween(color_correct_new(0, 1.0f, 1.0f, 1.0f),
						color_correct_new(0, 0.4f, 0.6f, 1.0f),
						t));
}

t_color_c	ray_tracing(t_ray ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hit_info;
	t_color_c	color;
	t_color_c	incoming_light;
	// bool		is_env;
	bool		is_specular;

	// is_env = true;
	incoming_light = color_correct_new(0, 0, 0, 0);
	color = color_correct_new(0, 1.0f, 1.0f, 1.0f);
	i = -1;
	while (++i < 3)
	{
		hit_info = intersect_list(minirt, &ray);
		if (hit_info.hit)
		{
			// is_env = false;
			ray.origin = hit_info.intersect_pt;
			hit_info.d_diffuse = random_vec3_hs(hit_info.normal, state);
			hit_info.d_diffuse = vec3_normalize(vec3_add(hit_info.d_diffuse,
															hit_info.normal));
			is_specular = hit_info.material.specular_i > random_num(state);
			if (is_specular)
			{
				hit_info.d_specular = reflection(ray.direction, hit_info.normal);
				ray.direction = vec3_tween(hit_info.d_diffuse,
											hit_info.d_specular,
											hit_info.material.reflective_i);
			}
			else
				ray.direction = hit_info.d_diffuse;
			ray.direction = random_vec3_hs(hit_info.normal, state);
			ray.direction = vec3_normalize(vec3_add(ray.direction,
													hit_info.normal));
			//ray->direction = vec3_normalize(vec3_cross(hit_info.normal,
			//		random_vec3_hs(hit_info.normal, state)));
			calculate_incoming(&incoming_light, &color, &hit_info.material, minirt, &hit_info);
			//calculate_incoming(&incoming_light, color,&hit_info.material, minirt, &hit_info);
			color = color_multiply(color, hit_info.material.color);
			// color = color_multiply(color, color_tween(hit_info.material.color,
			// 			hit_info.material.specular, (double)is_specular));
			// color = color_scale(color, 0.5f);
		}
		else
		{
			// calculate_incoming(&incoming_light, color,
			// 		&minirt->amb_light.material);
			// incoming_light = color_add(incoming_light,
			// 							color_multiply(get_env_light(&ray,
			// 														is_env),
			// 											color));
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
