/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/09/27 22:56:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	get_color(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	ret;
	t_color_c	tmp;
	t_vec3		reflect;
	t_pt_light	*pt_light;
	t_list 		*tmp_list;
	float		dot_prod;

	// t_vec3		reflected_ray;
	hi->pt_to_cam = vec3_subtract(vec3_add(rt->cam.origin, rt->cam.position),
		hi->intersect_pt);
	hi->pt_to_cam = vec3_normalize(hi->pt_to_cam);
	tmp_list = rt->pt_lights;
	while (tmp_list)
	{
		pt_light = (t_pt_light *)(tmp_list->content);
		hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
		hi->pt_to_l = vec3_normalize(hi->pt_to_l);
		dot_prod = vec3_dot(hi->pt_to_l, hi->normal);
		if (dot_prod > 1)
			dot_prod = 1;
		tmp = color_scale(color_multiply(pt_light->material.color,
				hi->material.color), dot_prod);
		ret = tmp;
		reflect = reflection(hi->pt_to_l, hi->normal);
		dot_prod = vec3_dot(reflect, hi->pt_to_cam);
		if (dot_prod < 0)
			dot_prod = 0;
		if (dot_prod > 1)
			dot_prod = 1;
		if (vec3_dot(hi->pt_to_l, hi->normal) <= 0)
			dot_prod = 0;
		// tmp = color_scale(color_correct_new(0, 1, 1, 1), hi->material.specular_i
		// 	* powf(dot_prod, hi->material.shininess));
		tmp = color_scale(hi->material.specular, hi->material.specular_i
			* powf(dot_prod, hi->material.shininess));
		ret = color_add(ret, tmp);
		tmp_list = tmp_list->next;
	}
	tmp = rt->amb_light.color;
	tmp = color_scale(tmp, rt->amb_light.ratio);
	tmp = color_multiply(tmp, hi->material.color);
	ret = color_add(ret, tmp);
	return (color_clamp(ret));
}
