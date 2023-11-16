/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 21:17:06 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef t_vec3	(*t_i_ft)(void *, t_ray *);

static void	set_intersect(t_hit_info *hi, t_vec3 intersect, t_object *tmp)
{
	if (intersect.z > 0 && intersect.x > 0 && (hi->intersect.z == 0
			|| intersect.x < hi->intersect.x))
	{
		hi->intersect = intersect;
		hi->obj_type = tmp->type;
		hi->hit = true;
		hi->object = tmp;
	}
}

void	find_intersection(t_list *lst, t_ray *ray, t_hit_info *hi)
{
	t_vec3			intersect;
	t_object		*tmp;
	const t_i_ft	intersect_ft[] = {(t_i_ft)sphere_intersect,
		(t_i_ft)plane_intersect, (t_i_ft)cylinder_intersect,
		(t_i_ft)cone_intersect};

	ft_memset(&intersect, 0, sizeof(t_vec3));
	while (lst)
	{
		tmp = (t_object *)lst->content;
		if (!bound_box_intersect(tmp->bounding_box, *ray))
		{
			lst = lst->next;
			continue ;
		}
		intersect = (*intersect_ft[tmp->type])(tmp->object, ray);
		set_intersect(hi, intersect, tmp);
		lst = lst->next;
	}
}

void	find_selection_plane(t_minirt *minirt, t_ray *ray, t_hit_info *hi)
{
	t_vec3	intersect;

	if (minirt->selection.translation_plane)
	{
		intersect = plane_intersect(minirt->selection.translation_plane, ray);
		if (intersect.z > 0 && intersect.x > 0 && (hi->intersect.z == 0
				|| intersect.x < hi->intersect.x))
			hi->hit_selection_plane = true;
	}
	if (minirt->selection.rotation_plane)
	{
		intersect = sc_interesect(minirt->selection.rotation_plane, ray,
				minirt->selection.rotation_start, minirt->selection.angle);
		if (intersect.z > 0 && intersect.x > 0 && (hi->intersect.z == 0
				|| intersect.x < hi->intersect.x))
			hi->hit_rotation_plane = true;
	}
}

// iterates through the object list and calculates which intersection is the
// closest for one ray
t_hit_info	intersect_list(t_minirt *minirt, t_ray *ray)
{
	t_hit_info	hi;

	ft_memset(&hi, 0, sizeof(t_hit_info));
	find_intersection(minirt->objects, ray, &hi);
	find_selection_plane(minirt, ray, &hi);
	if (hi.hit == false)
		return (hi);
	hi.intersect_pt = vec3_multiply(ray->direction, hi.intersect.x);
	hi.intersect_pt = vec3_add(ray->origin, hi.intersect_pt);
	get_normal(&hi);
	return (hi);
}
