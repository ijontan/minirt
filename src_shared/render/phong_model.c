/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/11/08 15:42:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_l_block(t_hit_info *hi, t_minirt *rt, t_list **tmp_list)
{
	t_ray		ray;
	t_hit_info	hi2;
	float		dist;

	ray.origin = hi->intersect_pt;
	ray.direction = vec3_normalize(hi->pt_to_l);
	hi2 = intersect_list(rt, &ray);
	dist = vec3_length(vec3_subtract(ray.origin, hi2.intersect_pt));
	if (!hi2.hit || dist >= vec3_length(hi->pt_to_l))
		return (true);
	*tmp_list = (*tmp_list)->next;
	return (false);
}

static bool	is_outline(t_minirt *rt, t_hit_info *hi)
{
	float	dot_prod;

	if (rt->selection.selected == hi->object)
	{
		dot_prod = vec3_dot(hi->pt_to_cam, hi->normal);
		if (dot_prod > 0 && dot_prod < 0.4)
			return (true);
	}
	return (false);
}

t_color_c	get_diffused_color(t_hit_info *hi, t_color_c ray_color)
{
	float		dot_prod;
	t_color_c	tmp;

	dot_prod = vec3_dot(hi->pt_to_l, hi->normal);
	if (dot_prod <= 0)
		return (color_correct_new(0, 0, 0, 0));
	dot_prod = float_clamp(dot_prod, 0, 1);
	tmp = color_multiply(hi->material.color, ray_color);
	return (color_scale(tmp, dot_prod * hi->material.diffuse_i));
}

t_color_c	get_specular_color(t_hit_info *hi, t_color_c ray_color)
{
	t_vec3		reflect;
	float		dot_prod;
	t_color_c	tmp;

	reflect = reflection(hi->pt_to_l, hi->normal);
	dot_prod = vec3_dot(reflect, hi->pt_to_cam);
	if (dot_prod <= 0 || vec3_dot(hi->pt_to_l, hi->normal) <= 0)
		return (color_correct_new(0, 0, 0, 0));
	dot_prod = float_clamp(dot_prod, 0, 1);
	tmp = color_multiply(hi->material.specular, ray_color);
	return (color_scale(tmp, hi->material.specular_i * powf(dot_prod,
				hi->material.shininess)));
}

t_color_c	get_lights_color(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	ret;
	t_list		*tmp_list;
	t_pt_light	*pt_light;

	hi->pt_to_cam = vec3_subtract(vec3_add(rt->cam.origin, rt->cam.position),
			hi->intersect_pt);
	hi->pt_to_cam = vec3_normalize(hi->pt_to_cam);
	ret = color_correct_new(0, 0, 0, 0);
	if (is_outline(rt, hi))
		return (rt->selection.outline_color);
	tmp_list = rt->pt_lights;
	while (tmp_list)
	{
		pt_light = (t_pt_light *)(tmp_list->content);
		hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
		if (!check_l_block(hi, rt, &tmp_list))
			continue ;
		hi->pt_to_l = vec3_normalize(hi->pt_to_l);
		ret = color_add(ret, get_diffused_color(hi, pt_light->material.color));
		ret = color_add(ret, get_specular_color(hi, pt_light->material.color));
		tmp_list = tmp_list->next;
	}
	return (ret);
}

/**
 * @brief Get the color object
 * first get the color from the lights
 * then add the ambient light
 * ambient light is calculated with ambient color * ambient ratio * object color
 *
 * @param rt
 * @param hi
 */
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
