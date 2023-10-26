/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:17:20 by rsoo              #+#    #+#             */
/*   Updated: 2023/10/03 14:44:17 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// co is the vector from the tip of the cone to the ray origin
t_vec3	cone_intersect(t_cone *cone, t_ray *ray)
{
	t_vec3	abc;
	t_vec3	co;
	float	discriminant;
	float	sqrtd;
	t_vec3	sols;

	if (cone->angle <= 0 || cone->angle >= M_PI * 0.5)
		return (vec3_new(0, 0, 0));
	co = vec3_subtract(ray->origin, cone->tip);

	abc.x = ft_power(vec3_dot(ray->direction, cone->normalized_axis), 2)
			- cone->cos_squared;

	abc.y = (vec3_dot(ray->direction, cone->normalized_axis) *
			vec3_dot(co, cone->normalized_axis) -
			vec3_dot(ray->direction, co) * cone->cos_squared) * 2.0f;

	abc.z = ft_power(vec3_dot(co, cone->normalized_axis), 2) -
			vec3_dot(co, co) * cone->cos_squared;

	// printf("a %f, b %f, c %f\n", abc.x, abc.y, abc.z);

	discriminant = abc.y * abc.y - 4.0f * abc.x * abc.z;
	printf("disc %f\n", discriminant);
	if (discriminant < 0)
		return (vec3_new(0, 0, 0));
	sqrtd = ft_sqrt(discriminant);
	sols.z = 1.0f / (2.0f * abc.x);
	sols.x = (-abc.y - sqrtd) * sols.z;
	sols.y = (-abc.y + sqrtd) * sols.z;
	printf("t1 %f, t2 %f\n", sols.x, sols.y);
	sols.z = 2;
	if (sols.x > sols.y)
	{
		sqrtd = sols.x;
		sols.x = sols.y;
		sols.y = sqrtd;
	}
	return (sols);
}
