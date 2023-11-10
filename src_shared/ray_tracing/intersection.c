/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/11/08 15:30:30 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_hit_info	intersections(t_minirt *rt, t_ray *ray)
// {

// }

// iterates through the object list and calculates which intersection is the
// closest for one ray
t_hit_info	intersect_list(t_minirt *minirt, t_ray *ray)
{
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;
	t_list		*lst;
	t_object	*tmp;

	t_vec3 (*intersect_ft[])(void *, t_ray *) = {
		(t_vec3(*)(void *, t_ray *)) & sphere_intersect,
		(t_vec3(*)(void *, t_ray *)) & plane_intersect,
		(t_vec3(*)(void *, t_ray *)) & cylinder_intersect,
		(t_vec3(*)(void *, t_ray *)) & cone_intersect,
	};
	lst = minirt->objects;
	ft_memset(&prev_intersect, 0, sizeof(t_vec3));
	ft_memset(&intersect, 0, sizeof(t_vec3));
	ft_memset(&hit_info, 0, sizeof(t_hit_info));
	while (lst)
	{
		tmp = (t_object *)lst->content;
		if (!bound_box_intersect(tmp->bounding_box, *ray))
		{
			lst = lst->next;
			continue ;
		}
		intersect = (*intersect_ft[tmp->type])(tmp->object, ray);
		if (intersect.z > 0 && intersect.x > 0 && (prev_intersect.z == 0
				|| intersect.x < prev_intersect.x))
		{
			prev_intersect = intersect;
			hit_info.obj_type = tmp->type;
			hit_info.hit = true;
			hit_info.object = tmp;
		}
		lst = lst->next;
	}
	if (minirt->selection.translation_plane)
	{
		intersect = (*intersect_ft[PLANE])(minirt->selection.translation_plane,
				ray);
		if (intersect.z > 0 && intersect.x > 0 && (prev_intersect.z == 0
				|| intersect.x < prev_intersect.x))
			hit_info.hit_selection_plane = true;
	}
	if (minirt->selection.rotation_plane)
	{
		intersect = sc_interesect(minirt->selection.rotation_plane, ray,
				minirt->selection.rotation_start, minirt->selection.angle);
		if (intersect.z > 0 && intersect.x > 0 && (prev_intersect.z == 0
				|| intersect.x < prev_intersect.x))
			hit_info.hit_rotation_plane = true;
	}
	if (hit_info.hit == false)
		return (hit_info);
	hit_info.intersect_pt = vec3_multiply(ray->direction, prev_intersect.x);
	hit_info.intersect_pt = vec3_add(ray->origin, hit_info.intersect_pt);
	if (hit_info.obj_type == SPHERE)
	{
		hit_info.material = ((t_sphere *)hit_info.object->object)->material;
		hit_info.normal = ((t_sphere *)(hit_info.object->object))->center;
		hit_info.normal = vec3_subtract(hit_info.intersect_pt, hit_info.normal);
		hit_info.normal = vec3_normalize(hit_info.normal);
		if (hit_info.material.texture)
			hit_info.material.color = get_pixel_color(hit_info.material.texture,
					uv_sphere(hit_info.normal,
						hit_info.material.texture->size));
		if (hit_info.material.specular_map)
			hit_info.material.specular = get_pixel_color(hit_info.material.specular_map,
					uv_sphere(hit_info.normal,
						hit_info.material.norm_map->size));
		if (hit_info.material.norm_map)
		{
			intersect = get_pixel_vec3(hit_info.material.norm_map,
					uv_sphere(hit_info.normal,
						hit_info.material.norm_map->size));
			hit_info.normal = (t_vec3){.x = hit_info.normal.x * intersect.x,
				.y = hit_info.normal.y * intersect.y, .z = hit_info.normal.z
				* intersect.z};
			hit_info.normal = vec3_normalize(hit_info.normal);
		}
	}
	else if (hit_info.obj_type == PLANE)
	{
		hit_info.material = ((t_plane *)hit_info.object->object)->material;
		hit_info.normal = ((t_plane *)(hit_info.object->object))->rot_normal;
		if (vec3_dot(ray->direction, hit_info.normal) > 0)
			hit_info.normal = vec3_multiply(hit_info.normal, -1);
		hit_info.normal = vec3_normalize(hit_info.normal);
	}
	else if (hit_info.obj_type == CYLINDER)
	{
		hit_info.material = ((t_cylinder *)hit_info.object->object)->material;
		hit_info.normal = cylinder_normal((t_cylinder *)(hit_info.object->object),
				hit_info.intersect_pt, prev_intersect.z);
		hit_info.normal = vec3_normalize(hit_info.normal);
	}
	else if (hit_info.obj_type == CONE)
	{
		hit_info.material = ((t_cone *)hit_info.object->object)->material;
		hit_info.normal = cone_normal((t_cone *)(hit_info.object->object),
				hit_info.intersect_pt, prev_intersect.z);
		hit_info.normal = vec3_normalize(hit_info.normal);
	}
	return (hit_info);
}
