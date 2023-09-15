/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_apply_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:26:03 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 20:33:39 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_apply_rot(t_vec3 vec, t_quaternion rot)
{
	double	in[3];
	double	out[3];

	in[0] = (double)vec.x;
	in[1] = (double)vec.y;
	in[2] = (double)vec.z;
	quaternion_rotate(&rot, in, out);
	vec.x = (float)out[0];
	vec.y = (float)out[1];
	vec.z = (float)out[2];
	return (vec);
}
