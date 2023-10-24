/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 01:50:15 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_l_block(t_hit_info *hi, t_minirt *rt)
{
	t_ray		ray;
	t_hit_info	hi2;
	float		dist;

	ray.origin = hi->intersect_pt;
	ray.direction = hi->pt_to_l;
	hi2 = intersect_list(rt, &ray);
	dist = vec3_length(vec3_subtract(hi->intersect_pt, hi2.intersect_pt));
	if (hi2.hit && dist > 0 && dist < vec3_length(hi->pt_to_l))
		return (false);
	return (true);
}

t_color_c	get_lights_color(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	ret;
	t_color_c	tmp;
	t_list		*tmp_list;
	t_vec3		reflect;
	t_pt_light	*pt_light;
	float		dot_prod;

	hi->pt_to_cam = vec3_subtract(vec3_add(rt->cam.origin, rt->cam.position),
			hi->intersect_pt);
	hi->pt_to_cam = vec3_normalize(hi->pt_to_cam);
	tmp_list = rt->pt_lights;
	ret = color_correct_new(0, 0, 0, 0);
	// dot_prod = vec3_dot(hi->pt_to_cam, hi->normal);
	// if (dot_prod > 0 && dot_prod < 0.5)
	// 	return (rt->outline_color);
	while (tmp_list)
	{
		pt_light = (t_pt_light *)(tmp_list->content);
		hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
		if (!check_l_block(hi, rt))
		{
			// ret = color_correct_new(0, 1, 1, 0);
			tmp_list = tmp_list->next;
			continue ;
		}
		hi->pt_to_l = vec3_normalize(hi->pt_to_l);
		dot_prod = vec3_dot(hi->pt_to_l, hi->normal);
		if (dot_prod > 1)
			dot_prod = 0;
		tmp = color_scale(color_multiply(pt_light->material.color,
					hi->material.color), dot_prod);
		ret = color_add(ret, tmp);
		reflect = reflection(hi->pt_to_l, hi->normal);
		dot_prod = vec3_dot(reflect, hi->pt_to_cam);
		if (dot_prod <= 0)
			dot_prod = 0;
		if (dot_prod > 1)
			dot_prod = 1;
		if (vec3_dot(hi->pt_to_l, hi->normal) <= 0)
			dot_prod = 0;
		// tmp = color_scale(color_correct_new(0, 1, 1, 1),
		// hi->material.specular_i
		// 	* powf(dot_prod, hi->material.shininess));
		tmp = color_multiply(hi->material.specular, pt_light->material.color);
		tmp = color_scale(tmp, hi->material.specular_i * powf(dot_prod,
					hi->material.shininess));
		ret = color_add(ret, tmp);
		tmp_list = tmp_list->next;
	}
	return (ret);
}

t_color_c	get_color(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	ret;
	t_color_c	tmp;

	// t_vec3		reflected_ray;
	ret = get_lights_color(rt, hi);
	tmp = rt->amb_light.color;
	tmp = color_scale(tmp, rt->amb_light.ratio);
	tmp = color_multiply(tmp, hi->material.color);
	ret = color_add(ret, tmp);
	return (color_clamp(ret));
}
