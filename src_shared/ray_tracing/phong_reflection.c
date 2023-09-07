/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:59:42 by itan              #+#    #+#             */
/*   Updated: 2023/09/08 03:38:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_vector(t_minirt *rt, t_hit_info *hi)
{
	float	dot_prod;

	dot_prod = vec3_dot(hi->intersect_pt, hi->normal) * 2;
	hi->p_reflection = vec3_multiply(hi->normal, dot_prod);
	hi->p_reflection = vec3_subtract(hi->intersect_pt, hi->p_reflection);
	hi->p_reflection = vec3_normalize(hi->p_reflection);
	hi->pt_to_l = vec3_subtract(rt->light_source.position, hi->intersect_pt);
	hi->pt_to_l = vec3_normalize(hi->pt_to_l);
}

/**
 * @brief phone reflection
 * 
 * @param minirt 
 * @param hit_info 
 */

t_color_c	phong_reflection(t_minirt *minirt, t_ray *ray, t_hit_info *hit_info)
{
	t_color_c	amb;
	t_color_c	emission;
	t_color_c	diffuse;
	t_color_c	color;
	t_color_c	specular;
	float		dot_prod;

	calculate_vector(minirt, hit_info);
	amb = color_scale(minirt->amb_light.material.emission,
						minirt->amb_light.material.emission_i);
	emission = color_scale(hit_info->material.emission,
							hit_info->material.emission_i);
	// emission = color_correct_new(0, 0, 0, 0);
	dot_prod = vec3_dot(hit_info->pt_to_l, hit_info->p_reflection);
	if (dot_prod < 0)
		dot_prod = 0;
	diffuse = color_scale(hit_info->material.color,
							hit_info->material.diffuse_i * dot_prod);
	dot_prod = vec3_dot(hit_info->p_reflection, ray->direction);
	if (dot_prod < 0)
		dot_prod = 0;
	dot_prod = hit_info->material.specular_i * (float)ft_power(dot_prod,
			hit_info->material.shininess);
	specular = color_scale(hit_info->material.color, dot_prod);
	color = color_add(amb, emission);
	color = color_add(color, diffuse);
	color = color_add(color, specular);
	return (color);
}
