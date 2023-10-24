/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:06:22 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 02:40:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief get the length of a vector
 *
 * @param vec
 * @return float
 */
float	vec3_length(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

/**
 * @brief normalize a vector
 *
 * @param vec
 * @return t_vec3
 */
t_vec3	vec3_normalize(t_vec3 vec)
{
	float	len_div;

	len_div = 1.0f / sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (vec3_new(vec.x * len_div, vec.y * len_div, vec.z * len_div));
}

/**
 * @brief cross product of two vectors
 *
 * @param vec1
 * @param vec2
 * @return t_vec3
 */
t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x
			* vec2.z, vec1.x * vec2.y - vec1.y * vec2.x));
}

/**
 * @brief dot product of two vectors
 *
 * @param vec1
 * @param vec2
 * @return float
 */
float	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

/**
 * @brief linear interpolation between two vectors
 *
 * @param vec1
 * @param vec2
 * @param t
 * @return t_vec3
 */
t_vec3	vec3_tween(t_vec3 vec1, t_vec3 vec2, float t)
{
	return (vec3_new(vec1.x + (vec2.x - vec1.x) * t, vec1.y + (vec2.y - vec1.y)
			* t, vec1.z + (vec2.z - vec1.z) * t));
}
