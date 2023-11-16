/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:13:49 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 13:42:01 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_sphere_normal(t_hit_info *hi)
{
	t_vec3	n_from_map;
	t_vec3	t;
	t_vec3	b;
	t_vec3	n;

	hi->material = ((t_sphere *)hi->object->object)->material;
	hi->normal = sphere_normal((t_sphere *)(hi->object->object),
			hi->intersect_pt);
	if (hi->material.texture)
		hi->material.color = get_pixel_color(hi->material.texture,
				uv_sphere(hi->normal, hi->material.texture->size));
	if (hi->material.specular_map)
		hi->material.specular = get_pixel_color(hi->material.specular_map,
				uv_sphere(hi->normal, hi->material.specular_map->size));
	if (hi->material.norm_map)
	{
		n_from_map = get_pixel_vec3(hi->material.norm_map, uv_sphere(hi->normal,
					hi->material.norm_map->size));
		t = vec3_cross(hi->normal, (t_vec3){0, 0, 1});
		b = vec3_cross(hi->normal, t);
		n = vec3_add(vec3_multiply(t, n_from_map.x), vec3_multiply(b,
					n_from_map.y));
		hi->normal = vec3_normalize(vec3_add(hi->normal, n));
	}
}

void	get_plane_normal(t_hit_info *hi)
{
	hi->material = ((t_plane *)hi->object->object)->material;
	hi->normal = ((t_plane *)(hi->object->object))->rot_normal;
	hi->normal = vec3_multiply(hi->normal, -1);
}

void	get_cylinder_normal(t_hit_info *hi)
{
	hi->material = ((t_cylinder *)hi->object->object)->material;
	hi->normal = cylinder_normal((t_cylinder *)(hi->object->object),
			hi->intersect_pt, hi->intersect.z);
}

void	get_cone_normal(t_hit_info *hi)
{
	hi->material = ((t_cone *)hi->object->object)->material;
	hi->normal = cone_normal((t_cone *)(hi->object->object), hi->intersect_pt,
			hi->intersect.z);
}

typedef void	(*t_get_normal_ft)(t_hit_info *);

void	get_normal(t_hit_info *hi)
{
	const t_get_normal_ft	get_normal_ft[] = {&get_sphere_normal,
		&get_plane_normal, &get_cylinder_normal, &get_cone_normal};

	get_normal_ft[hi->object->type](hi);
}
