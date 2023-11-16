/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:56:25 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 17:38:28 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief get the normal of a cylinder
 *
 * @param cylinder
 * @param point
 * @return t_vec3
 */
t_vec3	cylinder_normal(t_cylinder *cylinder, t_vec3 point, float type)
{
	t_vec3	normal;
	t_vec3	oc;
	float	t;

	if (type == 3)
		return (cylinder->rot_axis);
	else if (type == 4)
		return (vec3_multiply(cylinder->rot_axis, -1));
	oc = vec3_subtract(point, cylinder->center);
	t = vec3_dot(oc, cylinder->rot_axis);
	normal = vec3_subtract(point, vec3_add(cylinder->center,
				vec3_multiply(cylinder->rot_axis, t)));
	if (type == 5)
		normal = vec3_multiply(normal, -1);
	return (vec3_normalize(normal));
}

// oi: origin (camera) to intersection
// co: centre to origin (camera)
// ci: centre to interesection
static float	ray_in_cylinder_bound(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_vec3	point;
	t_vec3	ci;
	float	distance;

	point = vec3_add(ray->origin, vec3_multiply(ray->direction, t));
	ci = vec3_subtract(point, cylinder->center);
	distance = vec3_dot(cylinder->rot_axis, ci);
	if (distance < cylinder->height * -0.5 || distance > cylinder->height * 0.5)
		return (distance);
	return (0);
}

// op: origin to point on the plane
// cp: centre of cylinder to point on the plane
t_vec3	cylinder_caps_intersect(t_cylinder *cylinder, t_ray *ray, bool is_top)
{
	t_plane	cap_plane;
	t_vec3	op;
	t_vec3	cp;
	t_vec3	sols;

	if (is_top)
		cp = vec3_multiply(cylinder->rot_axis, cylinder->height * 0.5);
	else
		cp = vec3_multiply(cylinder->rot_axis, cylinder->height * -0.5);
	op = vec3_add(cylinder->center, cp);
	if (is_top)
		cp = vec3_multiply(cylinder->rot_axis, -1);
	else
		cp = cylinder->rot_axis;
	cap_plane = (t_plane){.center = op, .rot_normal = cp,
		.r = cylinder->radius};
	sols = disk_intersect(&cap_plane, ray);
	if (is_top && sols.z > 0)
		sols.z = 3;
	else if (sols.z > 0)
		sols.z = 4;
	return (sols);
}

/**
 * @brief find the intersection of a ray and a cylinder
 *
 * @param cylinder
 * @param ray
 * @return t_vec3
 */
t_vec3	cylinder_intersect(t_cylinder *cylinder, t_ray *ray)
{
	t_vec3	abc;
	float	discriminant;
	t_ray	ray2;
	t_vec3	sols;
	float	distance;

	ray2.direction = vec3_cross(ray->direction, cylinder->rot_axis);
	ray2.origin = vec3_cross(vec3_subtract(ray->origin, cylinder->center),
			cylinder->rot_axis);
	abc.x = vec3_dot(ray2.direction, ray2.direction);
	abc.y = 2.0f * vec3_dot(ray2.origin, ray2.direction);
	abc.z = vec3_dot(ray2.origin, ray2.origin) - cylinder->radius
		* cylinder->radius;
	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	sols = calc_t(abc.x, abc.y, sqrtf(discriminant));
	swap_if_greater(&sols.x, &sols.y);
	distance = ray_in_cylinder_bound(cylinder, ray, sols.x);
	if (!distance)
		return (sols);
	return (cylinder_caps_intersect(cylinder, ray, distance > 0));
}
