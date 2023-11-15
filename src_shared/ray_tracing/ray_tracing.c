/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:40:55 by itan              #+#    #+#             */
/*   Updated: 2023/11/15 22:52:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	calculate_incoming(t_color_c *in_light, t_color_c *rayColor,
		t_material *material)
{
	t_color_c	emitting;

	emitting = material->emission;
	emitting = color_scale(emitting, material->emission_i);
	emitting = color_multiply(emitting, *rayColor);
	*in_light = color_add(*in_light, emitting);
}

void	calculate_deffuse(t_color_c *in_light, t_color_c *rayColor,
		t_minirt *rt, t_hit_info *hi)
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
		diffused = color_add(diffused, color_multiply(tmp, *rayColor));
		tmp_list = tmp_list->next;
	}
	*in_light = color_add(*in_light, diffused);
}

void	calculate_specular(t_color_c *in_light, t_color_c *rayColor,
		t_minirt *rt, t_hit_info *hi)
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
		diffused = color_add(diffused, color_multiply(tmp, *rayColor));
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
	t = bazier_curves_1d_cubic(0.5f * (ray->direction.y + 1.0f), (double[]){0,
			-3, 3.5, 1});
	return (color_tween(color_correct_new(0, 1.0f, 1.0f, 1.0f),
			color_correct_new(0, 0.4f, 0.6f, 1.0f), t));
}

t_color_c	ray_tracing(t_ray ray, t_minirt *minirt, unsigned int *state)
{
	int			i;
	t_hit_info	hit_info;
	t_color_c	ray_c;
	t_color_c	incoming_light;
	bool		is_specular;

	incoming_light = color_correct_new(0, 0, 0, 0);
	ray_c = color_correct_new(0, 1.0f, 1.0f, 1.0f);
	i = -1;
	while (++i < 5)
	{
		hit_info = intersect_list(minirt, &ray);
		if (hit_info.hit)
		{
			ray.origin = hit_info.intersect_pt;
			hit_info.d_diffuse = random_vec3_hs(hit_info.normal, state);
			hit_info.d_diffuse = vec3_normalize(vec3_add(hit_info.d_diffuse,
						hit_info.normal));
			is_specular = hit_info.material.specular_i > random_num(state);
			hit_info.pt_to_cam = vec3_subtract(vec3_add(minirt->cam.origin,
						minirt->cam.position), hit_info.intersect_pt);
			hit_info.pt_to_cam = vec3_normalize(hit_info.pt_to_cam);
			if (is_specular)
			{
				hit_info.d_specular = reflection(ray.direction,
						hit_info.normal);
				ray.direction = vec3_tween(hit_info.d_diffuse,
						hit_info.d_specular, hit_info.material.reflective_i);
				calculate_specular(&incoming_light, &ray_c, minirt, &hit_info);
			}
			else
			{
				ray.direction = hit_info.d_diffuse;
				calculate_deffuse(&incoming_light, &ray_c, minirt, &hit_info);
			}
			calculate_incoming(&incoming_light, &ray_c, &hit_info.material);
			ray_c = color_multiply(ray_c, color_tween(hit_info.material.color,
						hit_info.material.specular, (double)is_specular));
		}
		else
		{
			// calculate_incoming(&incoming_light, ray_c,
			// 		&minirt->amb_light.material);
			// incoming_light = color_add(incoming_light,
			// 							color_multiply(get_env_light(&ray,
			// 														is_env),
			// 											ray_c));
			break ;
		}
	}
	return (incoming_light);
}
