/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:06:22 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 03:04:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec3_length(t_vec3 vec)
{
	return (ft_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	float	len;

	len = vec3_length(vec);
	return (vec3_new(vec.x / len, vec.y / len, vec.z / len));
}

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x
			* vec2.z, vec1.x * vec2.y - vec1.y * vec2.x));
}

float	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
