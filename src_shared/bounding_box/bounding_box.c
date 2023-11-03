/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 00:32:55 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 17:07:13 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief new bounding box
 *
 * @param min
 * @param max
 * @return t_bound_box
 */
t_bound_box	bound_box_new(t_vec3 min, t_vec3 max)
{
	t_bound_box	bound_box;

	bound_box.min = min;
	bound_box.max = max;
	return (bound_box);
}

float	float_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	float_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * @brief expend a bounding box to include a point
 *
 * @param box
 * @param point
 * @return t_bound_box
 */
t_bound_box	bound_box_expand(t_bound_box box, t_vec3 point)
{
	t_bound_box	new_box;

	new_box.min = vec3_new(float_min(box.min.x, point.x), float_min(box.min.y,
				point.y), float_min(box.min.z, point.z));
	new_box.max = vec3_new(float_max(box.max.x, point.x), float_max(box.max.y,
				point.y), float_max(box.max.z, point.z));
	return (new_box);
}

static void	ft_swap_min(float *a, float *b)
{
	float	tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

/**
 * @brief find the intersection between a ray and a bounding box
 *
 * @param box
 * @param ray
 * @return true
 * @return false
 */
bool	bound_box_intersect(t_bound_box box, t_ray ray)
{
	t_vec3	tmin;
	t_vec3	tmax;

	tmin.x = (box.min.x - ray.origin.x) / ray.direction.x;
	tmax.x = (box.max.x - ray.origin.x) / ray.direction.x;
	tmax.y = (box.max.y - ray.origin.y) / ray.direction.y;
	tmin.y = (box.min.y - ray.origin.y) / ray.direction.y;
	tmin.z = (box.min.z - ray.origin.z) / ray.direction.z;
	tmax.z = (box.max.z - ray.origin.z) / ray.direction.z;
	ft_swap_min(&tmin.x, &tmax.x);
	ft_swap_min(&tmin.y, &tmax.y);
	ft_swap_min(&tmin.z, &tmax.z);
	return (tmin.x <= tmax.y && tmin.y <= tmax.x && tmin.x <= tmax.z
		&& tmin.z <= tmax.x && tmin.y <= tmax.z && tmin.z <= tmax.y);
}

t_bound_box	get_bound(t_object *obj)
{
	void			*object;
	unsigned char	type;

	object = obj->object;
	type = obj->type;
	if (type == SPHERE)
		obj->bounding_box = get_sphere_bound(object);
	else if (type == PLANE)
		obj->bounding_box = get_plane_bound(object);
	else if (type == CYLINDER)
		obj->bounding_box = get_cylinder_bound(object);
	else if (type == CONE)
		obj->bounding_box = get_cone_bound(object);
	return (obj->bounding_box);
}
