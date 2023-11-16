/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 01:49:15 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 01:49:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_deffuse(t_color_c *in_light, t_color_c *ray_c, t_minirt *rt,
		t_hit_info *hi)
{
	t_color_c	diffused;
	t_color_c	tmp;
	t_list		*tmp_list;
	t_pt_light	*pt_light;

	if (hi->material.diffuse_i == 0.0f)
		return ;
	ft_memset(&diffused, 0, sizeof(t_color_c));
	tmp_list = rt->pt_lights;
	while (tmp_list)
	{
		pt_light = (t_pt_light *)(tmp_list->content);
		hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
		if (!check_l_block(hi, rt, &tmp_list))
			continue ;
		hi->pt_to_l = vec3_normalize(hi->pt_to_l);
		tmp = get_diffused_color(hi, pt_light->material.color);
		diffused = color_add(diffused, color_multiply(tmp, *ray_c));
		tmp_list = tmp_list->next;
	}
	*in_light = color_add(*in_light, diffused);
}

void	calculate_specular(t_color_c *in_light, t_color_c *ray_c, t_minirt *rt,
		t_hit_info *hi)
{
	t_color_c	diffused;
	t_color_c	tmp;
	t_list		*tmp_list;
	t_pt_light	*pt_light;

	if (hi->material.specular_i == 0.0f)
		return ;
	ft_memset(&diffused, 0, sizeof(t_color_c));
	tmp_list = rt->pt_lights;
	while (tmp_list)
	{
		pt_light = (t_pt_light *)(tmp_list->content);
		hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
		if (!check_l_block(hi, rt, &tmp_list))
			continue ;
		hi->pt_to_l = vec3_normalize(hi->pt_to_l);
		tmp = get_specular_color(hi, pt_light->material.color);
		diffused = color_add(diffused, color_multiply(tmp, *ray_c));
		tmp_list = tmp_list->next;
	}
	*in_light = color_add(*in_light, diffused);
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
	t = bazier_curves_1d_cubic(0.5f * (ray->direction.y + 1.0f), (double []){0,
			-3, 3.5, 1});
	return (color_tween(color_correct_new(0, 1.0f, 1.0f, 1.0f),
			color_correct_new(0, 0.4f, 0.6f, 1.0f), t));
}
