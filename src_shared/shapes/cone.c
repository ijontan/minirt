/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:17:20 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 17:57:30 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cone_normal(t_cone *cone, t_vec3 point, float type)
{
	t_vec3	normal;
	t_vec3	co;
	float	m;

	if (type == 3)
		return (cone->rot_axis);
	co = vec3_subtract(point, cone->tip);
	m = vec3_dot(co, cone->rot_axis);
	normal = vec3_subtract(co, vec3_multiply(cone->rot_axis, m + 2));
	normal = vec3_normalize(normal);
	return (normal);
}

t_vec3	cone_cap_intersect(t_cone *cone, t_ray *ray)
{
	t_plane	cap_plane;
	t_vec3	op;
	t_vec3	cp;
	t_vec3	sols;

	cp = vec3_multiply(cone->rot_axis, cone->height);
	op = vec3_add(cone->tip, cp);
	cp = vec3_multiply(cone->rot_axis, -1);
	cap_plane = (t_plane){.center = op, .rot_normal = cp, .r = cone->radius};
	sols = disk_intersect(&cap_plane, ray);
	sols.z = 3;
	return (sols);
}

t_vec3	cone_get_t(t_cone *cone, t_ray *ray, t_vec3 sols)
{
	t_vec3	pt;
	float	h_pt;
	float	cam_angle;

	pt = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.x));
	h_pt = vec3_dot(vec3_subtract(pt, cone->tip), cone->rot_axis);
	if (h_pt < 0)
	{
		cam_angle = vec3_dot(ray->direction, cone->rot_axis);
		pt = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.y));
		h_pt = vec3_dot(vec3_subtract(pt, cone->tip), cone->rot_axis);
		if (cam_angle > cone->cos && h_pt < cone->height)
			return (vec3_new(sols.y, sols.x, sols.z));
		return (vec3_new(0, 0, 0));
	}
	cam_angle = vec3_dot(vec3_multiply(ray->direction, -1), cone->rot_axis)
		/ vec3_length(ray->direction);
	if (h_pt > cone->height || cam_angle > sqrt(cone->cos_squared))
		return (cone_cap_intersect(cone, ray));
	return (sols);
}

t_vec3	cone_intersect(t_cone *cone, t_ray *ray)
{
	t_vec3	abc;
	t_vec3	co;
	float	discriminant;
	t_vec3	sols;

	co = vec3_subtract(ray->origin, cone->tip);
	sols.x = vec3_dot(ray->direction, cone->rot_axis);
	sols.y = vec3_dot(co, cone->rot_axis);
	abc.x = ft_power(sols.x, 2) - vec3_dot(ray->direction, ray->direction)
		* cone->cos_squared;
	abc.y = (sols.x * sols.y - (vec3_dot(ray->direction, co)
				* cone->cos_squared)) * 2.0f;
	abc.z = ft_power(sols.y, 2) - (vec3_dot(co, co) * cone->cos_squared);
	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	sols = calc_t(abc.x, abc.y, ft_sqrt(discriminant));
	swap_if_greater(&sols.x, &sols.y);
	return (cone_get_t(cone, ray, sols));
}
