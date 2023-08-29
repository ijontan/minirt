/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:56:25 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 15:16:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cylinder_normal(t_cylinder *cylinder, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	oc;
	float	t;

	oc = vec3_subtract(point, cylinder->center);
	t = vec3_dot(oc, cylinder->normalized_axis);
	normal = vec3_subtract(point, vec3_add(cylinder->center,
			vec3_multiply(cylinder->normalized_axis, t)));
	return (vec3_normalize(normal));
}

t_vec3	cylinder_intersect(t_cylinder *cylinder, t_ray *ray)
{
	t_vec3	oc;
	t_vec3	abc;
	float	discriminant;
	t_ray	ray2;
	t_vec3	sols;

	ray2.direction = vec3_cross(ray->direction, cylinder->normalized_axis);
	oc = vec3_cross(vec3_subtract(ray->origin, cylinder->center),
		cylinder->normalized_axis);
	abc.x = vec3_dot(ray2.direction, ray2.direction);
	abc.y = 2.0f * vec3_dot(oc, ray2.direction);
	abc.z = vec3_dot(oc, oc) - cylinder->radius * cylinder->radius;
	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	discriminant = ft_sqrt(discriminant);
	sols.z = 2.0f * abc.x;
	sols.x = (-abc.y - discriminant) / sols.z;
	sols.y = (-abc.y + discriminant) / sols.z;
	sols.z = 2;
	if (sols.x > sols.y)
	{
		discriminant = sols.x;
		sols.x = sols.y;
		sols.y = discriminant;
	}
	return (sols);
}
