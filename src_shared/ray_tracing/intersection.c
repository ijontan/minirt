/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 00:53:34 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_hit_info	intersections(t_minirt *rt, t_ray *ray)
// {

// }

typedef t_vec3	(*t_ft_intersect)(void *, t_ray *);

// iterates through the object list and calculates which intersection is the
// closest for one ray
t_hit_info	intersect_list(t_minirt *minirt, t_ray *ray)
{
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;
	t_list		*lst;
	t_object	*tmp;

	const t_ft_intersect intersect_ft[3] = {
		(t_ft_intersect)&sphere_intersect,
		(t_ft_intersect)&plane_intersect,
		(t_ft_intersect)&cylinder_intersect,
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
			if (tmp->type == SPHERE)
				hit_info.material = ((t_sphere *)tmp->object)->material;
			else if (tmp->type == PLANE)
				hit_info.material = ((t_plane *)tmp->object)->material;
			else if (tmp->type == CYLINDER)
				hit_info.material = ((t_cylinder *)tmp->object)->material;
			prev_intersect = intersect;
			hit_info.obj_type = tmp->type;
			hit_info.hit = true;
			hit_info.object = tmp;
		}
		lst = lst->next;
	}
	if (hit_info.hit == false)
		return (hit_info);
	hit_info.intersect_pt = vec3_multiply(ray->direction, prev_intersect.x);
	hit_info.intersect_pt = vec3_add(ray->origin, hit_info.intersect_pt);
	if (hit_info.obj_type == SPHERE)
	{
		hit_info.normal = ((t_sphere *)(hit_info.object->object))->center;
		hit_info.normal = vec3_subtract(hit_info.intersect_pt, hit_info.normal);
	}
	else if (hit_info.obj_type == PLANE)
	{
		hit_info.normal = ((t_plane *)(hit_info.object->object))->normalized_norm_vec;
		hit_info.normal = vec3_multiply(hit_info.normal, -1);
		hit_info.normal = vec3_normalize(hit_info.normal);
	}
	else if (hit_info.obj_type == CYLINDER)
	{
		hit_info.normal = cylinder_normal((t_cylinder *)(hit_info.object->object),
				hit_info.intersect_pt, prev_intersect.z);
	}
	hit_info.normal = vec3_normalize(hit_info.normal);
	return (hit_info);
}

// t_hit_info	intersections(t_minirt *minirt, t_ray *ray, unsigned int *state)
// {
// 	t_vec3		prev_intersect;
// 	t_vec3		intersect;
// 	t_hit_info	hit_info;

// 	(void)state;
// 	prev_intersect = vec3_new(0, 0, 0);
// 	hit_info.hit = false;
// 	hit_info.obj_type = 0;

// 	// sphere intersect
// 	intersect = sphere_intersect(&minirt->sphere, ray);
// 	// printf("sphere intersection: %f\n", intersect.z);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->sphere.material;
// 			hit_info.obj_type = SPHERE;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}

// 	// cylinder intersect
// 	intersect = cylinder_intersect(&minirt->cylinder, ray);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->cylinder.material;
// 			hit_info.obj_type = 2;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}

// 	// plane intersect
// 	intersect = plane_intersect(&minirt->plane, ray);
// 	// printf("plane intersection: %f\n", intersect.z);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->plane.material;
// 			hit_info.obj_type = 3;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}
// 	// printf("\n");
// 	hit_info.intersect_pt = prev_intersect;
// 	return (hit_info);
// }
