/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:17:37 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 15:52:13 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief create a new vector
 *
 * @param x
 * @param y
 * @param z
 * @return t_vec3
 */
t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

/**
 * @brief random vector to any direction
 *
 * @param state
 * @return t_vec3
 */
t_vec3	random_vec3(unsigned int *state)
{
	t_vec3	vec;

	vec.x = normal_dist_random_num(state) - 0.5;
	vec.y = normal_dist_random_num(state) - 0.5;
	vec.z = normal_dist_random_num(state) - 0.5;
	return (vec3_normalize(vec));
}

/**
 * @brief random vector to a hemisphere
 *
 * @param normal
 * @param state
 * @return t_vec3
 */
t_vec3	random_vec3_hs(t_vec3 normal, unsigned int *state)
{
	t_vec3	vec;

	vec = random_vec3(state);
	if (vec3_dot(vec, normal) < 0)
		vec = vec3_multiply(vec, -1);
	return (vec);
}
