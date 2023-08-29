/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:39:47 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 10:21:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	plane_intersect(t_plane *plane, t_ray *ray)
{
	float	denom;
	t_vec3	p0_l0;

	denom = vec3_dot(plane->normalized_norm_vec, ray->direction);
	if (denom > 1e-6)
	{
		p0_l0 = vec3_normalize(vec3_subtract(\
		plane->point_on_plane, ray->origin));
		plane->t = vec3_dot(p0_l0, plane->normalized_norm_vec) / denom;
		return (plane->t >= 0);
	}
	return (false);
}

t_vec3	plane_intersect_solution(t_plane *plane, t_ray *ray)
{
	t_vec3	solution;

	if (!plane_intersect(plane, ray))
		return (vec3_new(0, 0, 0));
	solution.x = ray->origin.x + ray->direction.x * plane->t;
	solution.y = ray->origin.y + ray->direction.y * plane->t;
	solution.z = ray->origin.z + ray->direction.z * plane->t;
	return (solution);
}

// typedef struct s_plane
// {
// 	t_vec3		point_on_plane;
// 	t_vec3		normalized_norm_vec;
// 	t_color_c	color;
// }				t_plane;

// typedef struct s_ray
// {
// 	t_vec3			origin;
// 	t_vec3			direction;
// 	float			intensity;
// 	t_color_c		color;
// }					t_ray;
