/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/09/10 12:22:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	calculate_incoming(t_color_c *in_light, t_color_c rayColor,
// 		t_minirt *minirt, t_hit_info *hit_info)
void	calculate_incoming(t_color_c *in_light, t_color_c rayColor,
		t_material *material)
{
	t_color_c	emitting;

	emitting = material->emission;
	emitting = color_scale(emitting, material->emission_i);
	// emitting = phong_reflection(minirt, hit_info);
	emitting = color_multiply(emitting, rayColor);
	*in_light = color_add(*in_light, emitting);
}

t_vec3	reflect(t_vec3 d_ray, t_vec3 normal)
{
	float	dot_prod;
	t_vec3	d_specular;

	dot_prod = vec3_dot(d_ray, normal) * 2;
	d_specular = vec3_subtract(d_ray, normal);
	d_specular = vec3_multiply(d_specular, dot_prod);
	d_specular = vec3_normalize(d_specular);
	return (d_specular);
}

t_color_c	ray_tracing(t_ray ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hit_info;
	t_color_c	color;
	t_color_c	incoming_light;

	incoming_light = color_correct_new(0, 0, 0, 0);
	color = color_correct_new(0, 1.0f, 1.0f, 1.0f);
	i = -1;
	while (++i < 3)
	{
		hit_info = intersect_list(minirt, &ray);
		if (hit_info.hit)
		{
			ray.origin = hit_info.intersect_pt;
			// hit_info.d_diffuse = random_vec3_hs(hit_info.normal, state);
			// hit_info.d_diffuse = vec3_normalize(vec3_add(hit_info.d_diffuse,
			// 												hit_info.normal));
			// hit_info.d_specular = reflect(ray.direction, hit_info.normal);
			// ray.direction = vec3_tween(hit_info.d_diffuse,
			// 							hit_info.d_specular,
			// 							0.5f);
			ray.direction = random_vec3_hs(hit_info.normal, state);
			ray.direction = vec3_normalize(vec3_add(ray.direction,
													hit_info.normal));
			// ray->direction = vec3_normalize(vec3_cross(hit_info.normal,
			// 		random_vec3_hs(hit_info.normal, state)));
			calculate_incoming(&incoming_light, color, &hit_info.material);
			// calculate_incoming(&incoming_light, color, minirt, &hit_info);
			color = color_multiply(color, hit_info.material.color);
			// color = color_scale(color, 0.5f);
		}
		else
		{
			// calculate_incoming(&incoming_light, color,
			// 		&minirt->amb_light.material);
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
