/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:20:11 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:44:40 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

/* ---------------------------------- vec3 ---------------------------------- */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

t_vec3		reflection(t_vec3 d_ray, t_vec3 normal);
t_vec3		vec3_apply_rot(t_vec3 vec, t_quaternion rot);
t_vec3		vec3_new(float x, float y, float z);
float		vec3_length(t_vec3 vec);
t_vec3		vec3_normalize(t_vec3 vec);
t_vec3		vec3_cross(t_vec3 vec1, t_vec3 vec2);
float		vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_tween(t_vec3 vec1, t_vec3 vec2, float t);
t_vec3		vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_subtract(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_multiply(t_vec3 vec, float scale);
t_vec3		vec3_divide(t_vec3 vec, float scale);
#endif