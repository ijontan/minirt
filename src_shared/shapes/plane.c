/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:39:47 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/03 16:52:53 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	plane_new(t_vec3 point, t_vec3 dir, t_material material)
{
	t_plane	plane;

	plane.center = point;
	plane.normal = dir;
	plane.rot_normal = dir;
	plane.material = material;
	return (plane);
}

// p: the intersection point of the ray and the plane
// p0: the centre of the disk
t_vec3	disk_intersect(t_plane *plane, t_ray *ray)
{
	t_vec3	sols;
	t_vec3	p;
	float	len;

	sols = plane_intersect(plane, ray);
	if (!sols.x && !sols.y && !sols.z)
		return (vec3_new(0, 0, 0));
	p = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.x));
	len = vec3_length(vec3_subtract(p, plane->center));
	if (len > plane->r)
		return (vec3_new(0, 0, 0));
	return (vec3_new(sols.x, 0, 2));
}

t_vec3	sc_interesect(t_plane *plane, t_ray *ray, t_vec3 start, float angle)
{
	t_vec3	sols;
	t_vec3	p;
	float	len;
	float	p_angle;

	sols = plane_intersect(plane, ray);
	if (!sols.x && !sols.y && !sols.z)
		return (vec3_new(0, 0, 0));
	p = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.x));
	len = vec3_length(vec3_subtract(p, plane->center));
	if (len > plane->r)
		return (vec3_new(0, 0, 0));
	p_angle = vec3_dot(vec3_normalize(vec3_subtract(p, plane->center)),
			vec3_normalize(start));
	if (p_angle < cos(angle))
		return (vec3_new(0, 0, 0));
	return (vec3_new(sols.x, 0, 2));
}

/**
 * @brief find the intersection of a ray and a plane
 *
 * @param plane
 * @param ray
 * @return t_vec3, x is theintersection,
	z is a bool to indicate if there is an intersection
 */
t_vec3	plane_intersect(t_plane *plane, t_ray *ray)
{
	float	denom;
	t_vec3	p0_l0;
	float	t;

	denom = vec3_dot(plane->rot_normal, vec3_normalize(ray->direction));
	if (denom > 1e-4)
	{
		p0_l0 = vec3_subtract(plane->center, ray->origin);
		t = vec3_dot(p0_l0, plane->rot_normal) / denom;
		return (vec3_new(t, 0, 2));
	}
	return (vec3_new(0, 0, 0));
}
