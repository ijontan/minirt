/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:59:42 by itan              #+#    #+#             */
/*   Updated: 2023/09/10 13:17:55 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_vector(t_minirt *rt, t_hit_info *hi)
{
	float	dot_prod;

	hi->pt_to_l = vec3_subtract(rt->light_source.position, hi->intersect_pt);
	hi->pt_to_l = vec3_normalize(hi->pt_to_l);
	dot_prod = vec3_dot(hi->pt_to_l, hi->normal) * 2;
	hi->d_specular = vec3_multiply(hi->normal, dot_prod);
	hi->d_specular = vec3_subtract(hi->d_specular, hi->pt_to_l);
	hi->d_specular = vec3_normalize(hi->d_specular);
	hi->pt_to_cam = vec3_subtract(rt->cam.origin, hi->intersect_pt);
}

/**
 * @brief phone reflection
 *
 * @param minirt
 * @param hit_info
 */

t_color_c	phong_reflection(t_minirt *minirt, t_hit_info *hit_info)
{
	t_color_c	amb;
	t_color_c	emission;
	t_color_c	diffuse;
	t_color_c	color;
	t_color_c	specular;
	float		dot_prod;

	calculate_vector(minirt, hit_info);
	amb = color_scale(minirt->amb_light.color,
						minirt->amb_light.ratio);
	// amb = color_correct_new(0, 0, 0, 0);
	emission = color_scale(hit_info->material.emission,
							hit_info->material.emission_i);
	// emission = color_correct_new(0, 0, 0, 0);
	dot_prod = vec3_dot(hit_info->pt_to_l, hit_info->normal);
	if (dot_prod < 0)
		dot_prod = 0;
	diffuse = color_scale(hit_info->material.color, hit_info->material.diffuse_i
			* dot_prod);
	dot_prod = vec3_dot(hit_info->d_specular, hit_info->pt_to_cam);
	if (dot_prod < 0)
		dot_prod = 0;
	dot_prod = hit_info->material.specular_i * powf(dot_prod,
			hit_info->material.shininess);
	specular = color_scale(hit_info->material.specular, dot_prod);
	color = color_add(amb, emission);
	color = color_add(color, diffuse);
	color = color_add(color, specular);
	if (color.b > 1)
		color.b = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.r > 1)
		color.r = 1;
	return (color);
}
