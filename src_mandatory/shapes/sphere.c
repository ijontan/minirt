/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:04:34 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 11:24:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	sphere_new(t_vec3 center, float radius, t_color_c color)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

t_vec3	sphere_normal(t_sphere *sphere, t_vec3 point)
{
	return (vec3_normalize(vec3_subtract(point, sphere->center)));
}

t_vec3	sphere_intersect(t_sphere *sphere, t_ray ray)
{
	t_vec3	oc;
	t_vec3	abc;
	float	discriminant;
	float	sqrtd;
	t_vec3	sols;

	oc = vec3_subtract(ray.origin, sphere->center);
	abc.x = vec3_dot(ray.direction, ray.direction);
	abc.y = 2.0f * vec3_dot(oc, ray.direction);
	abc.z = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	// if (discriminant < 0)
	// 	return (false);
	// return (true);
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	sqrtd = ft_sqrt(discriminant);
	sols.z = 2.0f * abc.x;
	sols.x = (-abc.y - sqrtd) / sols.z;
	sols.y = (-abc.y + sqrtd) / sols.z;
	sols.z = 2;
	if (sols.x > sols.y)
	{
		sqrtd = sols.x;
		sols.x = sols.y;
		sols.y = sqrtd;
	}
	return (sols);
}
