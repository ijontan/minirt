/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:17:20 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/02 16:06:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cone_normal(t_cone *cone, t_vec3 point, float type)
{
	t_vec3	normal;
	t_vec3	co;
	float	m;

	if (type == 3)
		return (cone->normalized_axis);
	co = vec3_subtract(point, cone->tip);
	m = vec3_dot(co, cone->normalized_axis);
	normal = vec3_subtract(co, vec3_multiply(cone->normalized_axis, m + 2));
	normal = vec3_normalize(normal);
	return (normal);
}

// t_vec3	cone_intersect(t_cone *cone, t_ray *ray)
// {
// 	t_vec3	abc;
// 	t_vec3	co;
// 	float	discriminant;
// 	float	sqrtd;
// 	t_vec3	sols;

// 	co = vec3_subtract(ray->origin, cone->tip);
// 	abc.x = vec3_dot(ray->direction, cone->normalized_axis)
// 		* vec3_dot(ray->direction, cone->normalized_axis)
// 		- vec3_dot(ray->direction, ray->direction) * cone->cos_squared;
// 	abc.y = 2.0f * (vec3_dot(ray->direction, cone->normalized_axis)
// 			* vec3_dot(co, cone->normalized_axis) - vec3_dot(ray->direction, co)
// 			* cone->cos_squared);
// 	abc.z = vec3_dot(co, cone->normalized_axis) * vec3_dot(co,
// 			cone->normalized_axis) - vec3_dot(co, co) * cone->cos_squared;
// 	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
// 	if (discriminant < 0)
// 		return (vec3_new(0, 0, 0));
// 	sqrtd = ft_sqrt(discriminant);
// 	sols.z = 1.0f / (2.0f * abc.x);
// 	sols.x = (-abc.y - sqrtd) * sols.z;
// 	sols.y = (-abc.y + sqrtd) * sols.z;
// 	sols.z = 2;
// 	if (sols.x > sols.y)
// 	{
// 		sqrtd = sols.x;
// 		sols.x = sols.y;
// 		sols.y = sqrtd;
// 	}
// 	return (sols);
// }

t_vec3	cone_cap_intersect(t_cone *cone, t_ray *ray)
{
	t_plane	cap_plane;
	t_vec3	op;
	t_vec3	cp;
	t_vec3	sols;

	cp = vec3_multiply(cone->normalized_axis, cone->height);
	op = vec3_add(cone->tip, cp);
	cp = vec3_multiply(cone->normalized_axis, -1);
	cap_plane = (t_plane){.point_on_plane = op, .normalized_norm_vec = cp,
		.r = cone->radius};
	sols = disk_intersect(&cap_plane, ray);
	sols.z = 3;
	return (sols);
}

t_vec3	cone_intersect(t_cone *cone, t_ray *ray)
{
	t_vec3	abc;
	t_vec3	co;
	float	discriminant;
	float	sqrtd;
	t_vec3	sols;

	co = vec3_subtract(ray->origin, cone->tip);
	sols.x = vec3_dot(ray->direction, cone->normalized_axis); // d.v
	sols.y = vec3_dot(co, cone->normalized_axis);             // co.v
	abc.x = ft_power(sols.x, 2) - vec3_dot(ray->direction, ray->direction)
		* cone->cos_squared;
	abc.y = (sols.x * sols.y - (vec3_dot(ray->direction, co)
				* cone->cos_squared)) * 2.0f;
	abc.z = ft_power(sols.y, 2) - (vec3_dot(co, co) * cone->cos_squared);
	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	sqrtd = ft_sqrt(discriminant);
	sols.z = 1.0f / (2.0f * abc.x);
	sols.x = (-abc.y - sqrtd) * sols.z;
	sols.y = (-abc.y + sqrtd) * sols.z;
	sols.z = 2;
	if (sols.x > sols.y || sols.x < 0)
	{
		sqrtd = sols.x;
		sols.x = sols.y;
		sols.y = sqrtd;
	}
	abc = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.x));
	sqrtd = vec3_dot(vec3_subtract(abc, cone->tip), cone->normalized_axis);
	if (sqrtd < 0)
	{
		discriminant = vec3_dot(ray->direction, cone->normalized_axis)
			/ vec3_length(ray->direction);
		abc = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.y));
		sqrtd = vec3_dot(vec3_subtract(abc, cone->tip), cone->normalized_axis);
		if (discriminant > sqrt(cone->cos_squared) && sqrtd < cone->height)
			return (vec3_new(sols.y, sols.x, sols.z));
		return (vec3_new(0, 0, 0));
	}
	discriminant = vec3_dot(vec3_multiply(ray->direction, -1),
			cone->normalized_axis) / vec3_length(ray->direction);
	if (sqrtd > cone->height || discriminant > sqrt(cone->cos_squared))
		return (cone_cap_intersect(cone, ray));
	return (sols);
}

// version 2
// t_vec3	cone_intersect(t_cone *cone, t_ray *ray)
// {
// 	t_vec3	abc;
// 	float	discriminant;
// 	float	sqrtd;
// 	t_vec3	sols;

// 	// if (cone->angle <= 0 || cone->angle >= M_PI * 0.5)
// 	// 	return (vec3_new(0, 0, 0));
// 	abc.x = ft_power(ray->direction.x, 2) + ft_power(ray->direction.y, 2)
// 		- ft_power(ray->direction.z, 2);
// 	abc.y = 2.0 * (ray->origin.x * ray->direction.x + ray->origin.y
// 			* ray->direction.y - ray->origin.z * ray->direction.z);
// 	abc.z = ft_power(ray->origin.x, 2) + ft_power(ray->origin.y, 2)
// 		- ft_power(ray->origin.z, 2);
// 	// printf("a %f, b %f, c %f\n\n", abc.x, abc.y, abc.z);
// 	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
// 	// printf("disc %f\n", discriminant);
// 	if (discriminant < 0)
// 		return (vec3_new(0, 0, 0));
// 	sqrtd = ft_sqrt(discriminant);
// 	sols.z = 1.0f / (2.0f * abc.x);
// 	sols.x = (-abc.y - sqrtd) * sols.z;
// 	sols.y = (-abc.y + sqrtd) * sols.z;
// 	// printf("t1 %f, t2 %f\n", sols.x, sols.y);
// 	sols.z = 2;
// 	if (sols.x > sols.y)
// 	{
// 		sqrtd = sols.x;
// 		sols.x = sols.y;
// 		sols.y = sqrtd;
// 	}
// 	return (sols);
// }
