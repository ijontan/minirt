/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:11:07 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:32:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief add two vectors
 * 
 * @param vec1 
 * @param vec2 
 * @return t_vec3 
 */
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

/**
 * @brief subtract two vectors
 * 
 * @param vec1 
 * @param vec2 
 * @return t_vec3 
 */
t_vec3	vec3_subtract(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

/**
 * @brief multiply a vector with a scalar
 * 
 * @param vec 
 * @param scale 
 * @return t_vec3 
 */
t_vec3	vec3_multiply(t_vec3 vec, float scale)
{
	return (vec3_new(vec.x * scale, vec.y * scale, vec.z * scale));
}

/**
 * @brief divide a vector with a scalar (slow)
 * 
 * @param vec 
 * @param scale 
 * @return t_vec3 
 */
t_vec3	vec3_divide(t_vec3 vec, float scale)
{
	float	div;

	div = 1 / scale;
	return (vec3_multiply(vec, div));
}
