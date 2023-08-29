/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:39:45 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 10:48:05 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	cylinder_intersect(t_cylinder *cylinder, t_ray *ray)
{

}

t_vec3	cylinder_intersect_solution(t_cylinder *cylinder, t_ray *ray)
{
	t_vec3	solution;

	if (!cylinder_intersect(cylinder, ray))
		return (vec3_new(0, 0, 0));

}

// typedef struct s_cylinder
// {
// 	t_vec3		center;
// 	t_vec3		normalized_axis;
// 	float		diameter;
// 	float		height;
// 	t_color_c	color;
// }				t_cylinder;

// typedef struct s_ray
// {
// 	t_vec3			origin;
// 	t_vec3			direction;
// 	float			intensity;
// 	t_color_c		color;
// }					t_ray;
