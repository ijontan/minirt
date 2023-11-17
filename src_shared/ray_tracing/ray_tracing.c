/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 02:20:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	calculate_incoming(t_color_c *in_light, t_color_c *ray_c,
		t_material *material)
{
	t_color_c	emitting;

	emitting = material->emission;
	emitting = color_scale(emitting, material->emission_i);
	emitting = color_multiply(emitting, *ray_c);
	*in_light = color_add(*in_light, emitting);
}

static void	prep_info(t_hit_info *hi, t_ray *ray, unsigned int *state)
{
	ray->origin = hi->intersect_pt;
	hi->d_diffuse = random_vec3_hs(hi->normal, state);
	hi->d_diffuse = vec3_normalize(vec3_add(hi->d_diffuse, hi->normal));
	hi->is_specular = hi->material.specular_i > random_num(state);
}

static void	handle_specular(t_ray *ray, t_minirt *rt, t_hit_info *hi)
{
	if (hi->is_specular)
	{
		hi->d_specular = reflection(ray->direction, hi->normal);
		ray->direction = vec3_tween(hi->d_diffuse, hi->d_specular,
				hi->material.reflective_i);
		calculate_specular(&ray->in_light, &ray->color, rt, hi);
	}
	else
	{
		ray->direction = hi->d_diffuse;
		calculate_deffuse(&ray->in_light, &ray->color, rt, hi);
	}
}

t_color_c	ray_tracing(t_ray ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hi;

	ray.color = color_correct_new(0, 1.0f, 1.0f, 1.0f);
	ray.in_light = color_correct_new(0, 0, 0, 0);
	i = -1;
	while (++i < 5)
	{
		hi = intersect_list(minirt, &ray);
		if (!hi.hit)
			break ;
		prep_info(&hi, &ray, state);
		handle_specular(&ray, minirt, &hi);
		calculate_incoming(&ray.in_light, &ray.color, &hi.material);
		ray.color = color_multiply(ray.color, color_tween(hi.material.color,
					hi.material.specular, (double)hi.is_specular));
	}
	return (ray.in_light);
}
