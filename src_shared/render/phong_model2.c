/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:17:18 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 18:17:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
